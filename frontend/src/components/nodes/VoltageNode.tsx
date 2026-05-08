import { Handle, Position } from '@xyflow/react';

export function VoltageNode({ data }: any) {
  return (
    <div className="bg-yellow-100 border-2 border-yellow-600 rounded-full w-16 h-16 flex flex-col items-center justify-center relative shadow-sm">
      <Handle type="source" position={Position.Top} id="pos" className="w-3 h-3 bg-red-500" />
      <Handle type="target" position={Position.Top} id="pos" className="w-3 h-3 bg-red-500" />
      
      <div className="text-xs font-bold font-mono">
        + {data.label || '5V'} -
      </div>
      
      <Handle type="source" position={Position.Bottom} id="neg" className="w-3 h-3 bg-black" />
      <Handle type="target" position={Position.Bottom} id="neg" className="w-3 h-3 bg-black" />
    </div>
  );
}
