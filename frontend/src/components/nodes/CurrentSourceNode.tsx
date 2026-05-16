import { Handle, Position } from '@xyflow/react';

export function CurrentSourceNode({ data }: any) {
  const label = data.label || '10mA';
  return (
    <div className="bg-white border-2 border-teal-700 rounded-full w-16 h-16 flex flex-col items-center justify-center relative shadow-sm">
      <Handle type="target" position={Position.Top} id="pos" className="w-3 h-3 bg-red-500" />
      <Handle type="source" position={Position.Top} id="pos" className="w-3 h-3 bg-red-500" />
      <Handle type="source" position={Position.Bottom} id="neg" className="w-3 h-3 bg-black" />
      <Handle type="target" position={Position.Bottom} id="neg" className="w-3 h-3 bg-black" />

      <svg width="28" height="28" viewBox="0 0 28 28" fill="none">
        {/* Arrow pointing up (current direction) */}
        <line x1="14" y1="24" x2="14" y2="6" stroke="#0d9488" strokeWidth="2" />
        <path d="M10,10 L14,4 L18,10" fill="none" stroke="#0d9488" strokeWidth="2" strokeLinejoin="round" />
      </svg>
      <div className="text-[9px] font-bold font-mono text-teal-800 leading-none">{label}</div>
    </div>
  );
}
