import { Handle, Position, useReactFlow } from '@xyflow/react';
import { useState, useRef, useCallback } from 'react';
import { Mic, Square } from 'lucide-react';

export function MicrophoneNode({ id, data }: any) {
  const [isRecording, setIsRecording] = useState(false);
  const [hasData, setHasData] = useState(!!data.pwlData);
  const mediaRecorder = useRef<MediaRecorder | null>(null);
  const chunks = useRef<Blob[]>([]);
  const { setNodes } = useReactFlow();

  const updatePwlData = useCallback((points: { t: number; v: number }[]) => {
    setNodes(nds => nds.map(n =>
      n.id === id
        ? { ...n, data: { ...n.data, pwlData: points } }
        : n
    ));
    setHasData(true);
  }, [id, setNodes]);

  const toggleRecord = async () => {
    if (isRecording) {
      if (mediaRecorder.current) {
        mediaRecorder.current.stop();
      }
      setIsRecording(false);
    } else {
      try {
        const stream = await navigator.mediaDevices.getUserMedia({ audio: true });
        mediaRecorder.current = new MediaRecorder(stream);
        chunks.current = [];
        
        mediaRecorder.current.ondataavailable = (e) => {
          chunks.current.push(e.data);
        };
        
        mediaRecorder.current.onstop = async () => {
          const blob = new Blob(chunks.current, { type: 'audio/webm' });
          const arrayBuffer = await blob.arrayBuffer();
          const audioCtx = new (window.AudioContext || (window as any).webkitAudioContext)();
          const audioBuffer = await audioCtx.decodeAudioData(arrayBuffer);
          
          const rawData = audioBuffer.getChannelData(0);
          const sampleRate = audioBuffer.sampleRate;
          
          // Take first 100ms of audio, decimated to ~8kHz to keep PWL manageable
          const targetDuration = 0.1; // 100ms
          const targetSampleRate = 8000;
          const decimationFactor = Math.max(1, Math.floor(sampleRate / targetSampleRate)); 
          const maxSamples = Math.min(sampleRate * targetDuration, rawData.length);
          const points: { t: number; v: number }[] = [];
          
          for (let i = 0; i < maxSamples; i += decimationFactor) {
            // Scale raw audio (-1..+1) to a small voltage (e.g. ±50mV typical electret mic level)
            points.push({ t: i / sampleRate, v: rawData[i] * 0.05 });
          }
          
          // Stop all tracks to release mic
          stream.getTracks().forEach(track => track.stop());
          audioCtx.close();

          // Properly update node data through React Flow state
          updatePwlData(points);
        };
        
        mediaRecorder.current.start();
        setIsRecording(true);
        
        // Auto stop after 1 second
        setTimeout(() => {
           if (mediaRecorder.current && mediaRecorder.current.state === 'recording') {
              mediaRecorder.current.stop();
              setIsRecording(false);
           }
        }, 1000);
      } catch (err) {
        console.error("Mic access denied", err);
      }
    }
  };

  return (
    <div className="bg-gray-100 border-2 border-gray-400 rounded-md p-2 w-20 flex flex-col items-center justify-center relative shadow-sm">
      <button 
        onClick={toggleRecord}
        className={`w-10 h-10 rounded-full flex items-center justify-center text-white ${isRecording ? 'bg-red-500 animate-pulse' : 'bg-gray-800'}`}
      >
        {isRecording ? <Square size={16} /> : <Mic size={16} />}
      </button>
      <div className="text-[10px] mt-1 font-mono">Microphone</div>
      {hasData && <div className="text-[8px] text-green-600 font-bold">● REC</div>}
      <Handle type="source" position={Position.Right} id="out" className="w-3 h-3 bg-blue-500" />
      <Handle type="source" position={Position.Bottom} id="gnd" className="w-3 h-3 bg-black" />
    </div>
  );
}
