import { Handle, Position } from '@xyflow/react';

export function PnpNode({ data }: any) {
  return (
    <div className="bg-gray-100 border-2 border-gray-400 rounded-md p-2 w-16 h-16 flex flex-col items-center justify-center relative shadow-sm">
      <Handle type="target" position={Position.Top} id="e" className="w-3 h-3 bg-red-500" style={{ left: '75%' }} />
      <Handle type="source" position={Position.Top} id="e" className="w-3 h-3 bg-red-500" style={{ left: '75%' }} />
      <Handle type="target" position={Position.Left} id="b" className="w-3 h-3 bg-purple-500" />
      <Handle type="source" position={Position.Left} id="b" className="w-3 h-3 bg-purple-500" />
      <Handle type="source" position={Position.Bottom} id="c" className="w-3 h-3 bg-black" style={{ left: '75%' }} />
      <Handle type="target" position={Position.Bottom} id="c" className="w-3 h-3 bg-black" style={{ left: '75%' }} />
      
      <svg viewBox="0 0 40 40" width="32" height="32" fill="none" stroke="currentColor" strokeWidth="2" strokeLinecap="round" strokeLinejoin="round" className="text-gray-800">
        <path d="M0 20 H 14" />
        <path d="M14 10 V 30" strokeWidth="4" />
        <path d="M14 16 L 26 4 V 0" />
        <path d="M14 24 L 26 36 V 40" />
        <path d="M14 16 L 20 17 M14 16 L 15 10" strokeWidth="2" />
      </svg>
      <div className="text-[10px] mt-1 font-mono text-gray-600">{data.label || 'PNP'}</div>
    </div>
  );
}
