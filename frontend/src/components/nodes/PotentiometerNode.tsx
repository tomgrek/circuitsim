import { Handle, Position } from '@xyflow/react';

export function PotentiometerNode({ data }: any) {
  const position = data.position ?? 50; // wiper position 0-100%
  const label = data.label || '10k';

  return (
    <div className="bg-white border-2 border-orange-700 rounded-md p-2 w-20 h-24 flex flex-col items-center justify-center relative shadow-sm">
      {/* Terminal handles */}
      <Handle type="target" position={Position.Left} id="in" className="w-3 h-3 bg-blue-500" style={{ top: '30%' }} />
      <Handle type="source" position={Position.Left} id="in" className="w-3 h-3 bg-blue-500" style={{ top: '30%' }} />
      <Handle type="source" position={Position.Right} id="out" className="w-3 h-3 bg-blue-500" style={{ top: '30%' }} />
      <Handle type="target" position={Position.Right} id="out" className="w-3 h-3 bg-blue-500" style={{ top: '30%' }} />
      <Handle type="target" position={Position.Top} id="wiper" className="w-3 h-3 bg-orange-500" />
      <Handle type="source" position={Position.Top} id="wiper" className="w-3 h-3 bg-orange-500" />

      {/* Symbol */}
      <svg width="56" height="28" viewBox="0 0 56 28" overflow="visible">
        {/* Resistor body */}
        <rect x="8" y="8" width="40" height="12" fill="none" stroke="#9a3412" strokeWidth="2" rx="2" />
        {/* Wiper arrow */}
        <line x1="28" y1="0" x2="28" y2="10" stroke="#c2410c" strokeWidth="2" />
        <path d="M24,6 L28,0 L32,6" fill="none" stroke="#c2410c" strokeWidth="1.5" />
        {/* Wiper position indicator */}
        <line x1={8 + (position / 100) * 40} y1="20" x2={8 + (position / 100) * 40} y2="26" stroke="#c2410c" strokeWidth="2" strokeDasharray="2,1" />
      </svg>

      <div className="text-[9px] font-bold font-mono text-orange-900 leading-none mt-1">
        {label} • {position}%
      </div>
    </div>
  );
}
