import { Handle, Position } from '@xyflow/react';
import { useEffect, useRef } from 'react';

export function LEDNode({ data }: any) {
  const color = (data.color as string) || 'red';
  const isExploded = !!data.isExploded;
  const max_current = data.max_current || 20;
  
  const glowRef = useRef<HTMLDivElement>(null);
  const textRef = useRef<HTMLDivElement>(null);

  useEffect(() => {
    if (isExploded || !data.current_array || !data.time_points) {
      if (textRef.current) textRef.current.innerText = '';
      return;
    }
    
    let animationFrame: number;
    let startTime = Date.now();
    const duration = data.time_points[data.time_points.length - 1] || 1000;
    
    const animate = () => {
      let elapsedMs = Date.now() - startTime;
      if (elapsedMs > duration) {
        startTime = Date.now();
        elapsedMs = 0;
      }
      
      let idx = 0;
      for (let i = 0; i < data.time_points.length; i++) {
        if (data.time_points[i] >= elapsedMs) {
          idx = i;
          break;
        }
      }
      
      const current = data.current_array[idx] || 0;
      let brightness = 0;
      if (current > 0.5) {
        brightness = Math.min(1, current / max_current);
      }
      
      if (glowRef.current) {
        glowRef.current.style.opacity = (0.3 + (brightness * 0.7)).toString();
        glowRef.current.style.boxShadow = brightness > 0 ? `0 0 ${10 + brightness * 20}px ${color}` : 'none';
      }
      if (textRef.current) {
        textRef.current.innerText = current.toFixed(1) + 'mA';
      }
      
      animationFrame = requestAnimationFrame(animate);
    };
    
    animationFrame = requestAnimationFrame(animate);
    return () => cancelAnimationFrame(animationFrame);
  }, [data.current_array, data.time_points, isExploded, max_current, color]);

  // static fallback
  const staticBrightness = typeof data.brightness === 'number' ? data.brightness : 0;
  const glowShadow = staticBrightness > 0 && !isExploded ? `0 0 ${10 + staticBrightness * 20}px ${color}` : 'none';
  const opacity = isExploded ? 0 : 0.3 + (staticBrightness * 0.7);

  return (
    <div className="bg-gray-100 border-2 border-gray-400 rounded-md p-2 w-16 h-16 flex flex-col items-center justify-center relative shadow-sm">
      <Handle type="target" position={Position.Top} id="anode" className="w-3 h-3 bg-red-500" />
      
      {isExploded ? (
        <div className="w-8 h-8 relative flex items-center justify-center">
          <svg width="32" height="32" viewBox="0 0 24 24" fill="none" stroke="black" strokeWidth="2" strokeLinecap="round" strokeLinejoin="round">
            <path d="M22 12h-4l-3 9L9 3l-3 9H2" />
            <line x1="4" y1="4" x2="20" y2="20" stroke="red" strokeWidth="3" />
            <line x1="20" y1="4" x2="4" y2="20" stroke="red" strokeWidth="3" />
          </svg>
        </div>
      ) : (
        <div 
          ref={glowRef}
          className="w-6 h-6 rounded-full"
          style={{ backgroundColor: color, boxShadow: glowShadow, opacity }}
        ></div>
      )}
      <div className="text-[10px] mt-1 font-mono">{data.label || 'LED'}</div>
      <div ref={textRef} className="text-[9px] font-mono font-bold text-gray-700 bg-gray-200 px-1 rounded absolute bottom-1 right-1"></div>

      <Handle type="source" position={Position.Bottom} id="cathode" className="w-3 h-3 bg-black" />
    </div>
  );
}
