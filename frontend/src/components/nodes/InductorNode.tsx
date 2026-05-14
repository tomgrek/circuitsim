import { Handle, Position } from '@xyflow/react';

export function InductorNode({ data }: any) {
  return (
    <div className="bg-white border-2 border-green-800 rounded-md p-2 w-16 h-16 flex items-center justify-center relative shadow-sm">
      <Handle type="target" position={Position.Left} id="in" className="w-3 h-3 bg-blue-500" />
      <Handle type="source" position={Position.Left} id="in" className="w-3 h-3 bg-blue-500" />
      
      <div className="flex flex-col items-center justify-center">
        <div className="flex items-center justify-center h-6">
          <svg width="32" height="12" viewBox="0 0 32 12">
            <path 
              d="M0 6 C 4 -6, 12 -6, 16 6 C 20 -6, 28 -6, 32 6" 
              fill="none" 
              stroke="#1f2937" 
              strokeWidth="2"
            />
          </svg>
        </div>
        <div className="text-[10px] font-bold font-mono mt-1 text-green-900">
          {data.label || '100uH'}
        </div>
      </div>
      
      <Handle type="source" position={Position.Right} id="out" className="w-3 h-3 bg-blue-500" />
      <Handle type="target" position={Position.Right} id="out" className="w-3 h-3 bg-blue-500" />
    </div>
  );
}
