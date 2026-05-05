import { Handle, Position } from '@xyflow/react';

export function ResistorNode({ data }: any) {
  return (
    <div className="bg-white border-2 border-gray-800 rounded-md p-2 w-24 h-12 flex items-center justify-center relative shadow-sm">
      <Handle type="target" position={Position.Left} id="in" className="w-3 h-3 bg-blue-500" />
      <div className="text-xs font-bold font-mono">
        {data.label || '1kΩ'}
      </div>
      <Handle type="source" position={Position.Right} id="out" className="w-3 h-3 bg-blue-500" />
    </div>
  );
}
