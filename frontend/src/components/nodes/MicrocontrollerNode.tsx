import { Handle, Position } from '@xyflow/react';

export function MicrocontrollerNode({ selected }: any) {
  return (
    <div className={`bg-gray-800 border-2 rounded w-24 shadow-md flex flex-col ${selected ? 'border-blue-500 shadow-lg shadow-blue-500/20' : 'border-gray-900'}`}>
      <div className="bg-gray-900 text-white text-[10px] font-bold text-center py-1 uppercase tracking-wider rounded-t">
        MCU
      </div>
      <div className="flex-1 flex justify-between py-2 relative h-32">
        {/* Left Side (Digital Pins) */}
        <div className="flex flex-col justify-around h-full items-start pl-1 z-10">
          <div className="relative flex items-center">
            <span className="text-gray-400 text-[8px] font-mono mr-1">D0</span>
            <Handle type="source" position={Position.Left} id="D0" className="w-2 h-2 !bg-blue-400 !border-gray-900 -ml-2" style={{ top: 'auto' }} />
          </div>
          <div className="relative flex items-center">
            <span className="text-gray-400 text-[8px] font-mono mr-1">D1</span>
            <Handle type="source" position={Position.Left} id="D1" className="w-2 h-2 !bg-blue-400 !border-gray-900 -ml-2" style={{ top: 'auto' }} />
          </div>
          <div className="relative flex items-center">
            <span className="text-gray-400 text-[8px] font-mono mr-1">D2</span>
            <Handle type="source" position={Position.Left} id="D2" className="w-2 h-2 !bg-blue-400 !border-gray-900 -ml-2" style={{ top: 'auto' }} />
          </div>
          <div className="relative flex items-center">
            <span className="text-gray-400 text-[8px] font-mono mr-1">D3</span>
            <Handle type="source" position={Position.Left} id="D3" className="w-2 h-2 !bg-blue-400 !border-gray-900 -ml-2" style={{ top: 'auto' }} />
          </div>
        </div>

        {/* Right Side (Analog, VCC, GND) */}
        <div className="flex flex-col justify-around h-full items-end pr-1 z-10">
          <div className="relative flex items-center justify-end">
            <Handle type="source" position={Position.Right} id="A0" className="w-2 h-2 !bg-green-400 !border-gray-900 -mr-2" style={{ top: 'auto' }} />
            <span className="text-gray-400 text-[8px] font-mono ml-1">A0</span>
          </div>
          <div className="relative flex items-center justify-end">
            <Handle type="source" position={Position.Right} id="A1" className="w-2 h-2 !bg-green-400 !border-gray-900 -mr-2" style={{ top: 'auto' }} />
            <span className="text-gray-400 text-[8px] font-mono ml-1">A1</span>
          </div>
          <div className="relative flex items-center justify-end">
            <Handle type="source" position={Position.Right} id="5V" className="w-2 h-2 !bg-red-500 !border-gray-900 -mr-2" style={{ top: 'auto' }} />
            <span className="text-gray-400 text-[8px] font-mono ml-1">5V</span>
          </div>
          <div className="relative flex items-center justify-end">
            <Handle type="source" position={Position.Right} id="GND" className="w-2 h-2 !bg-gray-400 !border-gray-900 -mr-2" style={{ top: 'auto' }} />
            <span className="text-gray-400 text-[8px] font-mono ml-1">GND</span>
          </div>
        </div>

        {/* Center decorative chip marking */}
        <div className="absolute inset-0 flex items-center justify-center pointer-events-none">
          <div className="w-8 h-8 rounded-full border border-gray-700 opacity-30"></div>
          <div className="absolute top-1 left-1/2 -translate-x-1/2 w-4 h-2 bg-gray-900 rounded-b-full"></div>
        </div>
      </div>
    </div>
  );
}
