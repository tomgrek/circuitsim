import { Handle, Position } from '@xyflow/react';
import { useEffect, useRef } from 'react';

export function SpeakerNode({ data }: any) {
  const audioCtx = useRef<AudioContext | null>(null);

  useEffect(() => {
    if (data.voltageData && data.voltageData.length > 0) {
      if (!audioCtx.current) {
        audioCtx.current = new (window.AudioContext || (window as any).webkitAudioContext)();
      }
      const ctx = audioCtx.current;
      if (ctx.state === 'suspended') ctx.resume();

      const sampleRate = ctx.sampleRate;
      // SPICE transient analysis usually has arbitrary time steps, 
      // but let's assume it's linearly interpolated or we just play it as is
      // A better way is to resample, but for simplicity we'll just map points.
      
      const durationSec = data.voltageData[data.voltageData.length - 1].t / 1000;
      const frameCount = Math.max(1, Math.floor(sampleRate * durationSec));
      const buffer = ctx.createBuffer(1, frameCount, sampleRate);
      const channelData = buffer.getChannelData(0);

      // Cubic Hermite Spline interpolation to audio sample rate
      let dataIdx = 0;
      for (let i = 0; i < frameCount; i++) {
        const t_ms = (i / sampleRate) * 1000;
        
        while (dataIdx < data.voltageData.length - 2 && data.voltageData[dataIdx + 1].t < t_ms) {
          dataIdx++;
        }
        
        const p0 = data.voltageData[Math.max(0, dataIdx - 1)];
        const p1 = data.voltageData[dataIdx];
        const p2 = data.voltageData[Math.min(data.voltageData.length - 1, dataIdx + 1)];
        const p3 = data.voltageData[Math.min(data.voltageData.length - 1, dataIdx + 2)];
        
        let v = p1.v;
        if (p2.t > p1.t) {
          const t = Math.max(0, Math.min(1, (t_ms - p1.t) / (p2.t - p1.t)));
          const t2 = t * t;
          const t3 = t2 * t;
          
          // Compute slopes (derivatives) with respect to time
          const m1 = (p2.v - p0.v) / (p2.t - p0.t || 1);
          const m2 = (p3.v - p1.v) / (p3.t - p1.t || 1);
          
          const dt = p2.t - p1.t;
          
          // Hermite basis functions
          const h00 = 2 * t3 - 3 * t2 + 1;
          const h10 = t3 - 2 * t2 + t;
          const h01 = -2 * t3 + 3 * t2;
          const h11 = t3 - t2;
          
          v = h00 * p1.v + h10 * dt * m1 + h01 * p2.v + h11 * dt * m2;
        }
        
        channelData[i] = Math.max(-1, Math.min(1, v / 5.0)); 
      }

      const source = ctx.createBufferSource();
      source.buffer = buffer;
      source.loop = true;
      source.connect(ctx.destination);
      source.start();
      
      return () => {
        try { source.stop(); } catch (e) {}
      };
    }
  }, [data.voltageData]);

  return (
    <div className="bg-gray-100 border-2 border-gray-400 rounded-md p-2 w-16 h-16 flex items-center justify-center relative shadow-sm">
      <Handle type="target" position={Position.Left} id="in" className="w-3 h-3 bg-blue-500" />
      <svg width="24" height="24" viewBox="0 0 24 24" fill="none" stroke="currentColor" strokeWidth="2">
        <polygon points="11 5 6 9 2 9 2 15 6 15 11 19 11 5" />
        <path d="M15.54 8.46a5 5 0 0 1 0 7.07" />
        <path d="M19.07 4.93a10 10 0 0 1 0 14.14" />
      </svg>
      <Handle type="source" position={Position.Bottom} id="gnd" className="w-3 h-3 bg-black" />
    </div>
  );
}
