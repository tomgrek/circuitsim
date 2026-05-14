import { Handle, Position } from '@xyflow/react';

export function SwitchNode({ data, selected }: any) {
  const isOpen = data.isOpen !== false; // Default to open
  
  return (
    <div className={`px-2 py-2 rounded bg-white border-2 ${selected ? 'border-blue-500 shadow-md' : 'border-gray-300'} min-w-[70px]`}>
      <Handle type="source" position={Position.Left} id="in" style={{ background: '#555' }} />
      <div className="flex flex-col items-center">
        <div className="relative w-12 h-10 flex items-center justify-center">
          <svg width="40" height="30" viewBox="0 0 40 30" className="absolute">
             <circle cx="10" cy="20" r="3" fill="#333" />
             <circle cx="30" cy="20" r="3" fill="#333" />
             <line 
               x1="10" y1="20" 
               x2="30" y2={isOpen ? "5" : "20"} 
               stroke="#333" strokeWidth="3" 
               strokeLinecap="round"
               style={{ transition: 'all 0.1s ease-in-out' }}
             />
          </svg>
        </div>
        <div className="text-[10px] font-bold text-gray-500 uppercase leading-none mt-1">{data.label || 'Switch'}</div>
        <div className={`text-[8px] font-bold ${isOpen ? 'text-red-500' : 'text-green-600'} mt-1`}>
          {isOpen ? 'OPEN' : 'CLOSED'}
        </div>
      </div>
      <Handle type="source" position={Position.Right} id="out" style={{ background: '#555' }} />
    </div>
  );
}
