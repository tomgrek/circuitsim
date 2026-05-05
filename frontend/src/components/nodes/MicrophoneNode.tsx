import { Handle, Position } from '@xyflow/react';
import { useState, useRef } from 'react';
import { Mic, Square } from 'lucide-react';

export function MicrophoneNode({ data }: any) {
  const [isRecording, setIsRecording] = useState(false);
  const mediaRecorder = useRef<MediaRecorder | null>(null);
  const chunks = useRef<Blob[]>([]);

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
          
          // Downsample or take first 100ms for SPICE (SPICE gets very slow with too many PWL points)
          const rawData = audioBuffer.getChannelData(0);
          const sampleRate = audioBuffer.sampleRate;
          
          // Take only first 100ms to match default sim time, and decimate to e.g. 10kHz to avoid massive PWL
          const targetDuration = 0.1; // 100ms
          const decimationFactor = Math.floor(sampleRate / 10000); 
          const points = [];
          
          for(let i=0; i < sampleRate * targetDuration && i < rawData.length; i += decimationFactor) {
            points.push({ t: i / sampleRate, v: rawData[i] });
          }
          
          // Pass data up via a custom event or let App.tsx pull it if we used React Flow's setNodes
          // For simplicity, we just mutate data here, though React Flow prefers immutable updates via onNodesChange
          data.pwlData = points;
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
      <Handle type="source" position={Position.Right} id="out" className="w-3 h-3 bg-blue-500" />
      <Handle type="source" position={Position.Bottom} id="gnd" className="w-3 h-3 bg-black" />
    </div>
  );
}
