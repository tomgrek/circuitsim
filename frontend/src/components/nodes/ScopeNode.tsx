import { Handle, Position } from '@xyflow/react';

export function ScopeNode({ data }: any) {
  const points1 = data.voltageData1 || data.voltageData || []; // Fallback for old 'voltageData'
  const points2 = data.voltageData2 || []; 
  
  const getPolyline = (points: {t: number, v: number}[], color: string) => {
    if (points.length === 0) return null;
    
    const allV = [...points1.map(p => p.v), ...points2.map(p => p.v)];
    const minV = allV.length > 0 ? Math.min(...allV) : -5;
    const maxV = allV.length > 0 ? Math.max(...allV) : 5;
    const range = Math.max(maxV - minV, 0.1);

    const polylinePoints = points.map((p: any, i: number) => {
      const x = (i / (points.length - 1)) * 100;
      const y = 60 - ((p.v - minV) / range) * 60;
      return `${x},${y}`;
    }).join(' ');

    return <polyline points={polylinePoints} fill="none" stroke={color} strokeWidth="1.5" />;
  };

  return (
    <div className="bg-gray-800 border-2 border-gray-900 rounded-md p-2 w-48 h-32 flex flex-col items-center relative shadow-lg">
      <div className="text-[10px] text-gray-300 mb-1 w-full text-center font-mono border-b border-gray-700 pb-1 flex justify-between px-1">
        <span className="text-yellow-400">CH1</span>
        <span>Oscilloscope</span>
        <span className="text-cyan-400">CH2</span>
      </div>
      <div className="bg-black w-full flex-1 rounded border border-gray-600 overflow-hidden relative flex items-center justify-center">
        {/* Grid lines */}
        <svg width="100%" height="100%" viewBox="0 0 100 60" preserveAspectRatio="none" className="absolute inset-0 opacity-20">
          <line x1="0" y1="30" x2="100" y2="30" stroke="white" strokeWidth="0.5" />
          <line x1="50" y1="0" x2="50" y2="60" stroke="white" strokeWidth="0.5" />
          <line x1="0" y1="15" x2="100" y2="15" stroke="white" strokeWidth="0.2" />
          <line x1="0" y1="45" x2="100" y2="45" stroke="white" strokeWidth="0.2" />
          <line x1="25" y1="0" x2="25" y2="60" stroke="white" strokeWidth="0.2" />
          <line x1="75" y1="0" x2="75" y2="60" stroke="white" strokeWidth="0.2" />
        </svg>

        {points1.length > 0 || points2.length > 0 ? (
          <svg width="100%" height="100%" viewBox="0 0 100 60" preserveAspectRatio="none" className="relative z-10">
            {getPolyline(points1, "#facc15")} {/* yellow-400 */}
            {getPolyline(points2, "#22d3ee")} {/* cyan-400 */}
          </svg>
        ) : (
          <span className="text-gray-500 text-[8px] uppercase tracking-wider">No Data</span>
        )}
      </div>
      
      {/* CH1 input (Bidirectional) */}
      <Handle type="target" position={Position.Left} id="ch1" className="w-3 h-3 bg-yellow-400" style={{ top: '30%' }} />
      <Handle type="source" position={Position.Left} id="ch1" className="w-3 h-3 bg-yellow-400" style={{ top: '30%' }} />
      {/* Fallback for old 'in' handle ID */}
      <Handle type="target" position={Position.Left} id="in" className="w-1 h-1 bg-transparent border-none opacity-0" style={{ top: '30%' }} />
      <div className="absolute left-1 top-[30%] translate-y-[-50%] text-[8px] text-yellow-400 font-bold pointer-events-none ml-3">CH1</div>
      
      {/* CH2 input (Bidirectional) */}
      <Handle type="target" position={Position.Left} id="ch2" className="w-3 h-3 bg-cyan-400" style={{ top: '60%' }} />
      <Handle type="source" position={Position.Left} id="ch2" className="w-3 h-3 bg-cyan-400" style={{ top: '60%' }} />
      <div className="absolute left-1 top-[60%] translate-y-[-50%] text-[8px] text-cyan-400 font-bold pointer-events-none ml-3">CH2</div>

      {/* GND input (Bidirectional) */}
      <Handle type="target" position={Position.Left} id="gnd" className="w-3 h-3 bg-gray-500" style={{ top: '90%' }} />
      <Handle type="source" position={Position.Left} id="gnd" className="w-3 h-3 bg-gray-500" style={{ top: '90%' }} />
      <div className="absolute left-1 top-[90%] translate-y-[-50%] text-[8px] text-gray-500 font-bold pointer-events-none ml-3">GND</div>
    </div>
  );
}
