import { Handle, Position } from '@xyflow/react';

export function ZenerDiodeNode({ data }: any) {
  return (
    <div className="bg-white border-2 border-gray-400 rounded-md p-2 w-16 h-16 flex flex-col items-center justify-center relative shadow-sm">
      <Handle type="target" position={Position.Left} id="anode" className="w-3 h-3 bg-gray-500" />
      <Handle type="source" position={Position.Left} id="anode" className="w-3 h-3 bg-gray-500" />
      
      <svg viewBox="0 0 40 40" width="32" height="32" fill="none" stroke="currentColor" strokeWidth="2" strokeLinecap="round" strokeLinejoin="round" className="text-gray-800">
        {/* Horizontal wire */}
        <path d="M0 20 H 12" />
        <path d="M28 20 H 40" />
        {/* Triangle (Anode to Cathode) */}
        <path d="M12 10 V 30 L 28 20 Z" fill="currentColor" />
        {/* Zener Bar (Cathode) */}
        <path d="M28 10 V 30" strokeWidth="3" />
        <path d="M28 10 H 32" strokeWidth="3" />
        <path d="M24 30 H 28" strokeWidth="3" />
      </svg>
      
      <div className="text-[10px] mt-1 font-mono text-gray-600">{data.label || '5.1V'}</div>
      
      <Handle type="source" position={Position.Right} id="cathode" className="w-3 h-3 bg-gray-500" />
      <Handle type="target" position={Position.Right} id="cathode" className="w-3 h-3 bg-gray-500" />
    </div>
  );
}
