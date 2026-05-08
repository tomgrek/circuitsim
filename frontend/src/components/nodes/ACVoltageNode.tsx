import { Handle, Position } from '@xyflow/react';

export function ACVoltageNode({ data }: any) {
  return (
    <div className="bg-white border-2 border-red-800 rounded-full w-16 h-16 flex items-center justify-center relative shadow-sm">
      <Handle type="source" position={Position.Top} id="pos" className="w-3 h-3 bg-red-500" />
      <Handle type="target" position={Position.Top} id="pos" className="w-3 h-3 bg-red-500" />
      
      <div className="flex flex-col items-center justify-center">
        <svg viewBox="0 0 24 24" width="24" height="24" fill="none" stroke="currentColor" strokeWidth="2" strokeLinecap="round" strokeLinejoin="round" className="text-red-800">
           <path d="M4 12 c 4 -8, 12 8, 16 0" />
        </svg>
        <div className="text-[10px] font-bold font-mono">
          {data.label || '10V 60Hz'}
        </div>
      </div>
      
      <Handle type="source" position={Position.Bottom} id="neg" className="w-3 h-3 bg-black" />
      <Handle type="target" position={Position.Bottom} id="neg" className="w-3 h-3 bg-black" />
    </div>
  );
}
