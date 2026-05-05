import { Handle, Position } from '@xyflow/react';

export function MultimeterNode({ data }: any) {
  const voltage = data.voltage !== undefined ? data.voltage.toFixed(3) : '0.000';
  return (
    <div className="bg-gray-800 border-2 border-gray-900 rounded-md p-3 w-32 flex flex-col items-center justify-center relative shadow-lg">
      <div className="bg-green-900 w-full h-10 rounded text-green-400 font-mono text-lg flex items-center justify-end px-2 mb-2 shadow-inner">
        {voltage} V
      </div>
      <div className="flex w-full justify-between px-4">
        <div className="text-red-500 font-bold text-xs">+</div>
        <div className="text-gray-400 font-bold text-xs">-</div>
      </div>
      <Handle type="target" position={Position.Bottom} id="pos" className="w-3 h-3 bg-red-500" style={{ left: '30%' }} />
      <Handle type="target" position={Position.Bottom} id="neg" className="w-3 h-3 bg-black" style={{ left: '70%' }} />
    </div>
  );
}
