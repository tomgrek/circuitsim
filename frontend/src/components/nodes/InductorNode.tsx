import { Handle, Position } from '@xyflow/react';

export function InductorNode({ data }: any) {
  return (
    <div className="bg-white border-2 border-green-800 rounded-md p-2 w-20 h-16 flex items-center justify-center relative shadow-sm">
      <Handle type="target" position={Position.Left} id="in" className="w-3 h-3 bg-blue-500" />
      <Handle type="source" position={Position.Left} id="in" className="w-3 h-3 bg-blue-500" />
      
      <div className="flex flex-col items-center justify-center">
        <div className="flex items-center justify-center h-8">
          {/* 3-bump inductor coil symbol */}
          <svg width="56" height="18" viewBox="0 0 56 18" overflow="visible">
            <line x1="0" y1="9" x2="4" y2="9" stroke="#065f46" strokeWidth="1.5" />
            <path
              d="M4,9 A6,6 0 0,1 16,9"
              fill="none" stroke="#065f46" strokeWidth="1.8"
            />
            <path
              d="M16,9 A6,6 0 0,1 28,9"
              fill="none" stroke="#065f46" strokeWidth="1.8"
            />
            <path
              d="M28,9 A6,6 0 0,1 40,9"
              fill="none" stroke="#065f46" strokeWidth="1.8"
            />
            <path
              d="M40,9 A6,6 0 0,1 52,9"
              fill="none" stroke="#065f46" strokeWidth="1.8"
            />
            <line x1="52" y1="9" x2="56" y2="9" stroke="#065f46" strokeWidth="1.5" />
          </svg>
        </div>
        <div className="text-[9px] font-bold font-mono text-green-900 leading-none">
          {data.label || '100uH'}
        </div>
      </div>
      
      <Handle type="source" position={Position.Right} id="out" className="w-3 h-3 bg-blue-500" />
      <Handle type="target" position={Position.Right} id="out" className="w-3 h-3 bg-blue-500" />
    </div>
  );
}
