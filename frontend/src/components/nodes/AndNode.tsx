import { Handle, Position } from '@xyflow/react';

export function AndNode() {
  return (
    <div className="bg-transparent w-24 h-24 relative flex items-center justify-center">
      <svg width="100%" height="100%" viewBox="0 0 100 100" className="absolute top-0 left-0 drop-shadow-md">
        <path d="M 20 20 L 50 20 A 30 30 0 0 1 50 80 L 20 80 Z" fill="white" stroke="#1f2937" strokeWidth="4" strokeLinejoin="round" />
        <text x="35" y="54" fontSize="12" fill="#1f2937" fontWeight="bold">AND</text>
      </svg>
      
      {/* Inputs */}
      <Handle type="target" position={Position.Left} id="in1" className="w-3 h-3 bg-blue-500 !top-[30%]" />
      <Handle type="source" position={Position.Left} id="in1" className="w-3 h-3 bg-blue-500 !top-[30%]" />
      <Handle type="target" position={Position.Left} id="in2" className="w-3 h-3 bg-blue-500 !top-[70%]" />
      <Handle type="source" position={Position.Left} id="in2" className="w-3 h-3 bg-blue-500 !top-[70%]" />
      
      {/* Output */}
      <Handle type="source" position={Position.Right} id="out" className="w-3 h-3 bg-blue-500 !top-[50%] !right-[15%]" />
      <Handle type="target" position={Position.Right} id="out" className="w-3 h-3 bg-blue-500 !top-[50%] !right-[15%]" />
    </div>
  );
}
