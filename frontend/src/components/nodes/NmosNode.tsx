import { Handle, Position } from '@xyflow/react';

export function NmosNode({ data }: any) {
  return (
    <div className="bg-gray-100 border-2 border-gray-400 rounded-md p-2 w-16 h-16 flex flex-col items-center justify-center relative shadow-sm">
      <Handle type="target" position={Position.Top} id="d" className="w-3 h-3 bg-blue-500" style={{ left: '75%' }} />
      <Handle type="target" position={Position.Left} id="g" className="w-3 h-3 bg-purple-500" />
      <Handle type="source" position={Position.Bottom} id="s" className="w-3 h-3 bg-black" style={{ left: '75%' }} />
      
      <svg viewBox="0 0 40 40" width="32" height="32" fill="none" stroke="currentColor" strokeWidth="2" strokeLinecap="round" strokeLinejoin="round" className="text-gray-800">
        <path d="M0 20 H 14" />
        <path d="M14 10 V 30" />
        <path d="M18 10 V 16 M18 18 V 22 M18 24 V 30" strokeWidth="3" />
        <path d="M18 12 H 26 V 0" />
        <path d="M18 28 H 26 V 40" />
        <path d="M18 20 H 26" />
        <path d="M22 17 L 18 20 L 22 23" />
      </svg>
      <div className="text-[10px] mt-1 font-mono text-gray-600">{data.label || 'NMOS'}</div>
    </div>
  );
}
