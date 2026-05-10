import { Handle, Position } from '@xyflow/react';

export function OpAmpNode() {
  return (
    <div className="bg-transparent w-24 h-24 relative flex items-center justify-center">
      {/* Triangle representation */}
      <svg width="100%" height="100%" viewBox="0 0 100 100" className="absolute top-0 left-0 drop-shadow-md">
        <polygon points="10,10 10,90 90,50" fill="white" stroke="#1f2937" strokeWidth="4" strokeLinejoin="round" />
        <text x="25" y="35" fontSize="12" fill="#1f2937" fontWeight="bold">-</text>
        <text x="25" y="75" fontSize="12" fill="#1f2937" fontWeight="bold">+</text>
        <text x="45" y="55" fontSize="10" fill="#1f2937" fontWeight="bold">LM358</text>
      </svg>
      
      {/* Handles */}
      {/* Inverting input */}
      <Handle type="target" position={Position.Left} id="in_inv" className="w-3 h-3 bg-blue-500 !top-[30%]" />
      <Handle type="source" position={Position.Left} id="in_inv" className="w-3 h-3 bg-blue-500 !top-[30%]" />
      {/* Non-inverting input */}
      <Handle type="target" position={Position.Left} id="in_non" className="w-3 h-3 bg-blue-500 !top-[70%]" />
      <Handle type="source" position={Position.Left} id="in_non" className="w-3 h-3 bg-blue-500 !top-[70%]" />
      
      {/* Output */}
      <Handle type="source" position={Position.Right} id="out" className="w-3 h-3 bg-blue-500 !top-[50%]" />
      <Handle type="target" position={Position.Right} id="out" className="w-3 h-3 bg-blue-500 !top-[50%]" />
      
      {/* Power pins (top/bottom) */}
      <Handle type="target" position={Position.Top} id="vcc" className="w-3 h-3 bg-red-500 !left-[50%]" />
      <Handle type="source" position={Position.Top} id="vcc" className="w-3 h-3 bg-red-500 !left-[50%]" />
      <Handle type="target" position={Position.Bottom} id="vee" className="w-3 h-3 bg-black !left-[50%]" />
      <Handle type="source" position={Position.Bottom} id="vee" className="w-3 h-3 bg-black !left-[50%]" />
    </div>
  );
}
