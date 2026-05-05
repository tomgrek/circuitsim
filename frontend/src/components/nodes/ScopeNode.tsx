import { Handle, Position } from '@xyflow/react';

export function ScopeNode({ data }: any) {
  const points = data.voltageData || []; // Array of {t, v}
  
  let polylinePoints = "";
  if (points.length > 0) {
    const minV = Math.min(...points.map((p: any) => p.v));
    const maxV = Math.max(...points.map((p: any) => p.v));
    const range = Math.max(maxV - minV, 0.1);
    
    // Scale to SVG 100x60
    polylinePoints = points.map((p: any, i: number) => {
      const x = (i / (points.length - 1)) * 100;
      const y = 60 - ((p.v - minV) / range) * 60;
      return `${x},${y}`;
    }).join(' ');
  }

  return (
    <div className="bg-gray-800 border-2 border-gray-900 rounded-md p-2 w-36 h-28 flex flex-col items-center relative shadow-lg">
      <div className="text-[10px] text-gray-300 mb-1 w-full text-center font-mono border-b border-gray-700 pb-1">Oscilloscope</div>
      <div className="bg-black w-full flex-1 rounded border border-gray-600 overflow-hidden relative flex items-center justify-center">
        {points.length > 0 ? (
          <svg width="100%" height="100%" viewBox="0 0 100 60" preserveAspectRatio="none">
            <polyline points={polylinePoints} fill="none" stroke="#22c55e" strokeWidth="1.5" />
          </svg>
        ) : (
          <span className="text-gray-500 text-[8px] uppercase tracking-wider">No Data</span>
        )}
      </div>
      <Handle type="target" position={Position.Left} id="in" className="w-3 h-3 bg-blue-500" />
      <Handle type="target" position={Position.Bottom} id="gnd" className="w-3 h-3 bg-black" style={{ left: '50%' }} />
    </div>
  );
}
