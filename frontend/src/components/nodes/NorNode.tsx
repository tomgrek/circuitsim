import { Handle, Position } from '@xyflow/react';

export function NorNode() {
  return (
    <div className="bg-transparent w-24 h-24 relative flex items-center justify-center">
      <svg width="100%" height="100%" viewBox="0 0 100 100" className="absolute top-0 left-0 drop-shadow-md">
        <path d="M 15 20 Q 50 20 75 50 Q 50 80 15 80 Q 30 50 15 20 Z" fill="white" stroke="#1f2937" strokeWidth="4" strokeLinejoin="round" />
        <circle cx="80" cy="50" r="5" fill="white" stroke="#1f2937" strokeWidth="4" />
        <text x="32" y="54" fontSize="12" fill="#1f2937" fontWeight="bold">NOR</text>
      </svg>
      
      {/* Inputs */}
      <Handle type="target" position={Position.Left} id="in1" className="w-3 h-3 bg-blue-500 !top-[30%] !left-[18%]" />
      <Handle type="source" position={Position.Left} id="in1" className="w-3 h-3 bg-blue-500 !top-[30%] !left-[18%]" />
      <Handle type="target" position={Position.Left} id="in2" className="w-3 h-3 bg-blue-500 !top-[70%] !left-[18%]" />
      <Handle type="source" position={Position.Left} id="in2" className="w-3 h-3 bg-blue-500 !top-[70%] !left-[18%]" />
      
      {/* Output */}
      <Handle type="source" position={Position.Right} id="out" className="w-3 h-3 bg-blue-500 !top-[50%] !right-[10%]" />
      <Handle type="target" position={Position.Right} id="out" className="w-3 h-3 bg-blue-500 !top-[50%] !right-[10%]" />
    </div>
  );
}
