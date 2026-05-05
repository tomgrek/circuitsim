import { Handle, Position } from '@xyflow/react';

export function CapacitorNode({ data }: any) {
  return (
    <div className="bg-white border-2 border-blue-800 rounded-md p-2 w-16 h-16 flex items-center justify-center relative shadow-sm">
      <Handle type="target" position={Position.Left} id="in" className="w-3 h-3 bg-blue-500" />
      <Handle type="source" position={Position.Left} id="in" className="w-3 h-3 bg-blue-500" />
      
      <div className="flex flex-col items-center justify-center">
        <div className="flex gap-1 h-6">
          <div className="w-1 bg-gray-800 h-full"></div>
          <div className="w-1 bg-gray-800 h-full"></div>
        </div>
        <div className="text-[10px] font-bold font-mono mt-1">
          {data.label || '10uF'}
        </div>
      </div>
      
      <Handle type="source" position={Position.Right} id="out" className="w-3 h-3 bg-blue-500" />
      <Handle type="target" position={Position.Right} id="out" className="w-3 h-3 bg-blue-500" />
    </div>
  );
}
