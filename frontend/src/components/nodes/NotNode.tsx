import { Handle, Position } from '@xyflow/react';

export function NotNode() {
  return (
    <div className="bg-transparent w-24 h-24 relative flex items-center justify-center">
      <svg width="100%" height="100%" viewBox="0 0 100 100" className="absolute top-0 left-0 drop-shadow-md">
        <polygon points="25,25 25,75 70,50" fill="white" stroke="#1f2937" strokeWidth="4" strokeLinejoin="round" />
        <circle cx="75" cy="50" r="5" fill="white" stroke="#1f2937" strokeWidth="4" />
        <text x="35" y="54" fontSize="12" fill="#1f2937" fontWeight="bold">NOT</text>
      </svg>
      
      {/* Input */}
      <Handle type="target" position={Position.Left} id="in1" className="w-3 h-3 bg-blue-500 !top-[50%] !left-[25%]" />
      <Handle type="source" position={Position.Left} id="in1" className="w-3 h-3 bg-blue-500 !top-[50%] !left-[25%]" />
      
      {/* Output */}
      <Handle type="source" position={Position.Right} id="out" className="w-3 h-3 bg-blue-500 !top-[50%] !right-[15%]" />
      <Handle type="target" position={Position.Right} id="out" className="w-3 h-3 bg-blue-500 !top-[50%] !right-[15%]" />
    </div>
  );
}
