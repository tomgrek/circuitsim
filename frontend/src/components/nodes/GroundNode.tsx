import { Handle, Position } from '@xyflow/react';

export function GroundNode() {
  return (
    <div className="flex flex-col items-center justify-center relative">
      <Handle type="target" position={Position.Top} id="in" className="w-3 h-3 bg-green-500" />
      <svg width="24" height="24" viewBox="0 0 24 24" fill="none" stroke="currentColor" strokeWidth="2" strokeLinecap="round" strokeLinejoin="round" className="mt-1 text-green-700">
        <path d="M12 2v8" />
        <path d="M4 10h16" />
        <path d="M7 14h10" />
        <path d="M10 18h4" />
      </svg>
    </div>
  );
}
