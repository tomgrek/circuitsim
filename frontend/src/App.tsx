import { useState, useCallback, useRef, useEffect, type DragEvent } from 'react';
import {
  ReactFlow,
  Controls,
  Background,
  applyNodeChanges,
  applyEdgeChanges,
  addEdge,
  type Node,
  type Edge,
  type NodeChange,
  type EdgeChange,
  type Connection,
  ReactFlowProvider,
  useReactFlow,
  ConnectionMode,
} from '@xyflow/react';
import '@xyflow/react/dist/style.css';

import { ResistorNode } from './components/nodes/ResistorNode';
import { VoltageNode } from './components/nodes/VoltageNode';
import { GroundNode } from './components/nodes/GroundNode';
import { LEDNode } from './components/nodes/LEDNode';
import { CapacitorNode } from './components/nodes/CapacitorNode';
import { Timer555Node } from './components/nodes/Timer555Node';
import { OpAmpNode } from './components/nodes/OpAmpNode';
import { MultimeterNode } from './components/nodes/MultimeterNode';
import { SignalGeneratorNode } from './components/nodes/SignalGeneratorNode';
import { ScopeNode } from './components/nodes/ScopeNode';
import { SpeakerNode } from './components/nodes/SpeakerNode';
import { MicrophoneNode } from './components/nodes/MicrophoneNode';
import { NpnNode } from './components/nodes/NpnNode';
import { PnpNode } from './components/nodes/PnpNode';
import { NmosNode } from './components/nodes/NmosNode';
import { PmosNode } from './components/nodes/PmosNode';
import { DiodeNode } from './components/nodes/DiodeNode';
import { ZenerDiodeNode } from './components/nodes/ZenerDiodeNode';
import { ACVoltageNode } from './components/nodes/ACVoltageNode';
import { MicrocontrollerNode } from './components/nodes/MicrocontrollerNode';
import { AndNode } from './components/nodes/AndNode';
import { OrNode } from './components/nodes/OrNode';
import { NotNode } from './components/nodes/NotNode';
import { NandNode } from './components/nodes/NandNode';
import { NorNode } from './components/nodes/NorNode';
import { XorNode } from './components/nodes/XorNode';
import { generateSpiceNetlist } from './utils/spice';
import { Play, Square, Trash2, Info } from 'lucide-react';
import { Simulation } from 'eecircuit-engine';
import { presets } from './utils/presets';
import { Logo } from './components/Logo';
import { DocsModal } from './components/DocsModal';

const nodeTypes = {
  resistor: ResistorNode,
  voltage: VoltageNode,
  ground: GroundNode,
  led: LEDNode,
  capacitor: CapacitorNode,
  timer555: Timer555Node,
  opamp: OpAmpNode,
  multimeter: MultimeterNode,
  signalgen: SignalGeneratorNode,
  scope: ScopeNode,
  speaker: SpeakerNode,
  microphone: MicrophoneNode,
  npn: NpnNode,
  pnp: PnpNode,
  nmos: NmosNode,
  pmos: PmosNode,
  diode: DiodeNode,
  zener: ZenerDiodeNode,
  acvoltage: ACVoltageNode,
  mcu: MicrocontrollerNode,
  and: AndNode,
  or: OrNode,
  not: NotNode,
  nand: NandNode,
  nor: NorNode,
  xor: XorNode,
};

let engineInstance: any = null;
let nodeId = 1;

function Sidebar() {
  const onDragStart = (event: DragEvent, nodeType: string, label?: string) => {
    event.dataTransfer.setData('application/reactflow', nodeType);
    if (label) event.dataTransfer.setData('application/reactflow-label', label);
    event.dataTransfer.effectAllowed = 'move';
  };

  return (
    <div className="w-64 bg-white border-r border-gray-200 p-4 flex flex-col gap-4 shadow-sm z-10 overflow-y-auto">
      <h2 className="font-semibold text-gray-700 text-sm uppercase tracking-wider mb-2">Components</h2>
      
      <div className="text-xs font-semibold text-gray-500 uppercase tracking-wider mb-2 mt-4">Transistors</div>
      <div className="grid grid-cols-2 gap-2">
        <div onDragStart={(event) => onDragStart(event, 'npn')} draggable className="bg-white border-2 border-gray-300 p-2 rounded cursor-grab hover:border-blue-500 transition-colors text-center shadow-sm">
          <div className="text-xs font-medium">NPN BJT</div>
        </div>
        <div onDragStart={(event) => onDragStart(event, 'pnp')} draggable className="bg-white border-2 border-gray-300 p-2 rounded cursor-grab hover:border-blue-500 transition-colors text-center shadow-sm">
          <div className="text-xs font-medium">PNP BJT</div>
        </div>
        <div onDragStart={(event) => onDragStart(event, 'nmos')} draggable className="bg-white border-2 border-gray-300 p-2 rounded cursor-grab hover:border-blue-500 transition-colors text-center shadow-sm">
          <div className="text-xs font-medium">NMOS</div>
        </div>
        <div onDragStart={(event) => onDragStart(event, 'pmos')} draggable className="bg-white border-2 border-gray-300 p-2 rounded cursor-grab hover:border-blue-500 transition-colors text-center shadow-sm">
          <div className="text-xs font-medium">PMOS</div>
        </div>
      </div>

      <div className="text-xs font-semibold text-gray-500 uppercase tracking-wider mb-2 mt-4">Logic Gates</div>
      <div className="grid grid-cols-2 gap-2">
        <div onDragStart={(event) => onDragStart(event, 'and')} draggable className="bg-white border-2 border-gray-300 p-2 rounded cursor-grab hover:border-blue-500 transition-colors text-center shadow-sm">
          <div className="text-xs font-medium">AND</div>
        </div>
        <div onDragStart={(event) => onDragStart(event, 'or')} draggable className="bg-white border-2 border-gray-300 p-2 rounded cursor-grab hover:border-blue-500 transition-colors text-center shadow-sm">
          <div className="text-xs font-medium">OR</div>
        </div>
        <div onDragStart={(event) => onDragStart(event, 'not')} draggable className="bg-white border-2 border-gray-300 p-2 rounded cursor-grab hover:border-blue-500 transition-colors text-center shadow-sm">
          <div className="text-xs font-medium">NOT</div>
        </div>
        <div onDragStart={(event) => onDragStart(event, 'nand')} draggable className="bg-white border-2 border-gray-300 p-2 rounded cursor-grab hover:border-blue-500 transition-colors text-center shadow-sm">
          <div className="text-xs font-medium">NAND</div>
        </div>
        <div onDragStart={(event) => onDragStart(event, 'nor')} draggable className="bg-white border-2 border-gray-300 p-2 rounded cursor-grab hover:border-blue-500 transition-colors text-center shadow-sm">
          <div className="text-xs font-medium">NOR</div>
        </div>
        <div onDragStart={(event) => onDragStart(event, 'xor')} draggable className="bg-white border-2 border-gray-300 p-2 rounded cursor-grab hover:border-blue-500 transition-colors text-center shadow-sm">
          <div className="text-xs font-medium">XOR</div>
        </div>
      </div>

      <div className="text-xs font-semibold text-gray-500 uppercase tracking-wider mb-2 mt-4">Tools</div>
      
      <div 
        className="border border-gray-300 rounded p-3 cursor-grab hover:bg-gray-50 flex flex-col items-center gap-2"
        onDragStart={(e) => onDragStart(e, 'voltage', '5V')} draggable
      >
        <div className="bg-yellow-100 border-2 border-yellow-600 rounded-full w-10 h-10 flex items-center justify-center font-bold text-[10px]">5V</div>
        <span className="text-sm font-medium">DC Voltage</span>
      </div>

      <div 
        className="border border-gray-300 rounded p-3 cursor-grab hover:bg-gray-50 flex flex-col items-center gap-2"
        onDragStart={(e) => onDragStart(e, 'ground')} draggable
      >
        <div className="flex flex-col items-center">
          <div className="w-1 h-3 bg-green-500"></div>
          <svg width="20" height="20" viewBox="0 0 24 24" fill="none" stroke="currentColor" strokeWidth="2" className="text-green-700">
            <path d="M4 10h16 M7 14h10 M10 18h4" />
          </svg>
        </div>
        <span className="text-sm font-medium">Ground</span>
      </div>

      <div 
        className="border border-gray-300 rounded p-3 cursor-grab hover:bg-gray-50 flex flex-col items-center gap-2"
        onDragStart={(e) => onDragStart(e, 'resistor', '1k')} draggable
      >
        <div className="bg-white border-2 border-gray-800 rounded w-16 h-6 flex items-center justify-center text-[10px] font-bold">1kΩ</div>
        <span className="text-sm font-medium">Resistor</span>
      </div>

      <div 
        className="border border-gray-300 rounded p-3 cursor-grab hover:bg-gray-50 flex flex-col items-center gap-2"
        onDragStart={(e) => onDragStart(e, 'capacitor', '10u')} draggable
      >
        <div className="bg-white border-2 border-blue-800 rounded w-10 h-10 flex flex-col items-center justify-center gap-1">
          <div className="flex gap-1 h-4">
            <div className="w-[2px] bg-gray-800 h-full"></div>
            <div className="w-[2px] bg-gray-800 h-full"></div>
          </div>
          <span className="text-[8px] font-bold">10uF</span>
        </div>
        <span className="text-sm font-medium">Capacitor</span>
      </div>

      <div 
        className="border border-gray-300 rounded p-3 cursor-grab hover:bg-gray-50 flex flex-col items-center gap-2"
        onDragStart={(e) => onDragStart(e, 'diode', '1N4148')} draggable
      >
        <div className="bg-white border-2 border-gray-400 rounded w-10 h-10 flex items-center justify-center">
           <svg viewBox="0 0 40 40" width="24" height="24" fill="none" stroke="currentColor" strokeWidth="2">
              <path d="M5 20 H 12 M28 20 H 35 M12 10 V 30 L 28 20 Z" fill="currentColor" />
              <path d="M28 10 V 30" strokeWidth="3" />
           </svg>
        </div>
        <span className="text-sm font-medium">Diode</span>
      </div>

      <div 
        className="border border-gray-300 rounded p-3 cursor-grab hover:bg-gray-50 flex flex-col items-center gap-2"
        onDragStart={(e) => onDragStart(e, 'zener', '5.1V')} draggable
      >
        <div className="bg-white border-2 border-gray-400 rounded w-10 h-10 flex items-center justify-center">
           <svg viewBox="0 0 40 40" width="24" height="24" fill="none" stroke="currentColor" strokeWidth="2">
              <path d="M5 20 H 12 M28 20 H 35 M12 10 V 30 L 28 20 Z" fill="currentColor" />
              <path d="M28 10 V 30 M28 10 H 32 M24 30 H 28" strokeWidth="3" />
           </svg>
        </div>
        <span className="text-sm font-medium">Zener</span>
      </div>

      <div 
        className="border border-gray-300 rounded p-3 cursor-grab hover:bg-gray-50 flex flex-col items-center gap-2"
        onDragStart={(e) => onDragStart(e, 'led')} draggable
      >
        <div className="bg-gray-100 border-2 border-gray-400 rounded w-10 h-10 flex flex-col items-center justify-center">
          <div className="w-4 h-4 bg-red-900 opacity-50 rounded-full"></div>
        </div>
        <span className="text-sm font-medium">LED</span>
      </div>

      <div 
        className="border border-gray-300 rounded p-3 cursor-grab hover:bg-gray-50 flex flex-col items-center gap-2"
        onDragStart={(e) => onDragStart(e, 'timer555')} draggable
      >
        <div className="bg-gray-800 border-2 border-gray-900 rounded w-16 h-10 flex items-center justify-center">
          <span className="text-white text-[10px] font-bold">NE555</span>
        </div>
        <span className="text-sm font-medium">555 Timer</span>
      </div>

      <div 
        className="border border-gray-300 rounded p-3 cursor-grab hover:bg-gray-50 flex flex-col items-center gap-2"
        onDragStart={(e) => onDragStart(e, 'mcu')} draggable
      >
        <div className="bg-gray-800 border-2 border-gray-900 rounded w-16 h-10 flex items-center justify-center">
          <span className="text-white text-[10px] font-bold">MCU</span>
        </div>
        <span className="text-sm font-medium">Microcontroller</span>
      </div>

      <div 
        className="border border-gray-300 rounded p-3 cursor-grab hover:bg-gray-50 flex flex-col items-center gap-2"
        onDragStart={(e) => onDragStart(e, 'opamp')} draggable
      >
        <div className="w-12 h-10 relative">
          <svg width="100%" height="100%" viewBox="0 0 100 100">
            <polygon points="10,10 10,90 90,50" fill="white" stroke="#1f2937" strokeWidth="4" />
          </svg>
        </div>
        <span className="text-sm font-medium">Op-Amp</span>
      </div>
      <div 
        className="border border-gray-300 rounded p-3 cursor-grab hover:bg-gray-50 flex flex-col items-center gap-2"
        onDragStart={(e) => onDragStart(e, 'multimeter')} draggable
      >
        <div className="bg-gray-800 border-2 border-gray-900 rounded w-16 h-10 flex items-center justify-center">
          <span className="text-green-400 text-[10px] font-mono">0.00 V</span>
        </div>
        <span className="text-sm font-medium">Multimeter</span>
      </div>

      <div 
        className="border border-gray-300 rounded p-3 cursor-grab hover:bg-gray-50 flex flex-col items-center gap-2"
        onDragStart={(e) => onDragStart(e, 'voltage', '5V')} draggable
      >
        <div className="bg-white border-2 border-red-800 rounded-full w-10 h-10 flex flex-col items-center justify-center">
          <span className="text-[10px] font-bold">+</span>
          <span className="text-[10px] font-bold">-</span>
        </div>
        <span className="text-sm font-medium text-center">DC Source</span>
      </div>

      <div 
        className="border border-gray-300 rounded p-3 cursor-grab hover:bg-gray-50 flex flex-col items-center gap-2"
        onDragStart={(e) => onDragStart(e, 'acvoltage', '10V 60Hz')} draggable
      >
        <div className="bg-white border-2 border-red-800 rounded-full w-10 h-10 flex flex-col items-center justify-center">
           <svg viewBox="0 0 24 24" width="16" height="16" fill="none" stroke="currentColor" strokeWidth="2" className="text-red-800">
             <path d="M4 12 c 4 -8, 12 8, 16 0" />
           </svg>
        </div>
        <span className="text-sm font-medium text-center">AC Source</span>
      </div>

      <div 
        className="border border-gray-300 rounded p-3 cursor-grab hover:bg-gray-50 flex flex-col items-center gap-2"
        onDragStart={(e) => onDragStart(e, 'signalgen')} draggable
      >
        <div className="bg-blue-100 border-2 border-blue-600 rounded w-16 h-10 flex flex-col items-center justify-center">
          <span className="text-blue-900 text-[8px] font-bold">~ SINE</span>
        </div>
        <span className="text-sm font-medium">Signal Gen</span>
      </div>

      <div 
        className="border border-gray-300 rounded p-3 cursor-grab hover:bg-gray-50 flex flex-col items-center gap-2"
        onDragStart={(e) => onDragStart(e, 'scope')} draggable
      >
        <div className="bg-gray-800 border-2 border-gray-900 rounded w-16 h-10 flex items-center justify-center overflow-hidden">
          <svg width="100%" height="100%" viewBox="0 0 100 60">
            <polyline points="0,30 25,10 50,50 75,10 100,30" fill="none" stroke="#22c55e" strokeWidth="4" />
          </svg>
        </div>
        <span className="text-sm font-medium">Oscilloscope</span>
      </div>

      <div 
        className="border border-gray-300 rounded p-3 cursor-grab hover:bg-gray-50 flex flex-col items-center gap-2"
        onDragStart={(e) => onDragStart(e, 'speaker')} draggable
      >
        <div className="bg-gray-100 border-2 border-gray-400 rounded w-10 h-10 flex items-center justify-center">
          <svg width="16" height="16" viewBox="0 0 24 24" fill="none" stroke="currentColor" strokeWidth="2">
            <polygon points="11 5 6 9 2 9 2 15 6 15 11 19 11 5" />
          </svg>
        </div>
        <span className="text-sm font-medium">Speaker</span>
      </div>

      <div 
        className="border border-gray-300 rounded p-3 cursor-grab hover:bg-gray-50 flex flex-col items-center gap-2"
        onDragStart={(e) => onDragStart(e, 'microphone')} draggable
      >
        <div className="bg-gray-100 border-2 border-gray-400 rounded w-10 h-10 flex items-center justify-center">
          <svg width="16" height="16" viewBox="0 0 24 24" fill="none" stroke="currentColor" strokeWidth="2">
            <path d="M12 2a3 3 0 0 0-3 3v7a3 3 0 0 0 6 0V5a3 3 0 0 0-3-3Z" />
            <path d="M19 10v2a7 7 0 0 1-14 0v-2" />
          </svg>
        </div>
        <span className="text-sm font-medium">Mic</span>
      </div>
    </div>
  );
}

function PropertiesPanel({ selectedNode, setNodes, isSimulating, runSimulation }: { selectedNode: Node, setNodes: any, isSimulating: boolean, runSimulation: () => void }) {
  if (!selectedNode) return null;

  const updateData = (key: string, value: any) => {
    setNodes((nds: Node[]) => nds.map(n => 
      n.id === selectedNode.id ? { ...n, data: { ...n.data, [key]: value } } : n
    ));
    if (isSimulating) {
      setTimeout(runSimulation, 50);
    }
  };

  return (
    <div className="w-64 bg-white border-l border-gray-200 p-4 shadow-sm z-10 overflow-y-auto">
      <h2 className="font-semibold text-gray-700 text-sm uppercase tracking-wider mb-4">Properties</h2>
      <div className="text-xs text-gray-500 mb-4 font-mono">ID: {selectedNode.id}</div>
      
      {selectedNode.type === 'voltage' && (
        <div className="mb-3">
          <label className="block text-xs font-medium text-gray-700 mb-1">Voltage (V)</label>
          <input type="text" value={(selectedNode.data.label as string) || '5V'} onChange={e => updateData('label', e.target.value)} className="w-full text-sm border border-gray-300 rounded px-2 py-1" />
        </div>
      )}
      {selectedNode.type === 'acvoltage' && (
        <>
          <div className="mb-3">
            <label className="block text-xs font-medium text-gray-700 mb-1">Amplitude (V)</label>
            <input type="number" step="1" value={(selectedNode.data.amplitude as number) || 10} onChange={e => { updateData('amplitude', parseFloat(e.target.value)); updateData('label', `${e.target.value}V ${selectedNode.data.frequency || 60}Hz`); }} className="w-full text-sm border border-gray-300 rounded px-2 py-1" />
          </div>
          <div className="mb-3">
            <label className="block text-xs font-medium text-gray-700 mb-1">Frequency (Hz)</label>
            <input type="number" step="1" value={(selectedNode.data.frequency as number) || 60} onChange={e => { updateData('frequency', parseFloat(e.target.value)); updateData('label', `${selectedNode.data.amplitude || 10}V ${e.target.value}Hz`); }} className="w-full text-sm border border-gray-300 rounded px-2 py-1" />
          </div>
        </>
      )}
      {selectedNode.type === 'resistor' && (
        <div className="mb-3">
          <label className="block text-xs font-medium text-gray-700 mb-1">Resistance (Ω)</label>
          <input type="text" value={(selectedNode.data.label as string) || '1k'} onChange={e => updateData('label', e.target.value)} className="w-full text-sm border border-gray-300 rounded px-2 py-1" />
        </div>
      )}
      {selectedNode.type === 'capacitor' && (
        <div className="mb-3">
          <label className="block text-xs font-medium text-gray-700 mb-1">Capacitance</label>
          <input type="text" value={(selectedNode.data.label as string) || '10u'} onChange={e => updateData('label', e.target.value)} className="w-full text-sm border border-gray-300 rounded px-2 py-1" />
        </div>
      )}
      {selectedNode.type === 'led' && (
        <>
          <div className="mb-3">
            <label className="block text-xs font-medium text-gray-700 mb-1">Color (CSS)</label>
            <input type="text" value={(selectedNode.data.color as string) || 'red'} onChange={e => updateData('color', e.target.value)} className="w-full text-sm border border-gray-300 rounded px-2 py-1" />
          </div>
          <div className="mb-3">
            <label className="block text-xs font-medium text-gray-700 mb-1">Forward Voltage Drop (V)</label>
            <input type="number" step="0.1" value={(selectedNode.data.v_drop as number) || 2.0} onChange={e => updateData('v_drop', parseFloat(e.target.value))} className="w-full text-sm border border-gray-300 rounded px-2 py-1" />
          </div>
          <div className="mb-3">
            <label className="block text-xs font-medium text-gray-700 mb-1">Max Current (mA)</label>
            <input type="number" value={(selectedNode.data.max_current as number) || 20} onChange={e => updateData('max_current', parseInt(e.target.value))} className="w-full text-sm border border-gray-300 rounded px-2 py-1" />
          </div>
          {selectedNode.data.isExploded && (
            <button 
              onClick={() => { updateData('isExploded', false); updateData('brightness', 0); }}
              className="w-full mt-2 bg-blue-500 hover:bg-blue-600 text-white font-semibold py-1 px-2 rounded shadow-sm text-sm"
            >
              Repair Component
            </button>
          )}
        </>
      )}
      {selectedNode.type === 'signalgen' && (
        <>
          <div className="mb-3">
            <label className="block text-xs font-medium text-gray-700 mb-1">Waveform</label>
            <select value={(selectedNode.data.waveform as string) || 'sine'} onChange={e => updateData('waveform', e.target.value)} className="w-full text-sm border border-gray-300 rounded px-2 py-1">
              <option value="sine">Sine</option>
              <option value="square">Square</option>
            </select>
          </div>
          <div className="mb-3">
            <label className="block text-xs font-medium text-gray-700 mb-1">Frequency (Hz)</label>
            <input type="number" value={(selectedNode.data.frequency as number) || 1} onChange={e => updateData('frequency', parseInt(e.target.value))} className="w-full text-sm border border-gray-300 rounded px-2 py-1" />
          </div>
          <div className="mb-3">
            <label className="block text-xs font-medium text-gray-700 mb-1">Amplitude (V)</label>
            <input type="number" value={(selectedNode.data.amplitude as number) || 5} onChange={e => updateData('amplitude', parseInt(e.target.value))} className="w-full text-sm border border-gray-300 rounded px-2 py-1" />
          </div>
        </>
      )}
      {selectedNode.type === 'mcu' && (
        <>
          <div className="mb-3">
            <label className="block text-xs font-medium text-gray-700 mb-1">Code (JS)</label>
            <textarea 
              value={(selectedNode.data.code as string) ?? "pinMode('D0', 'OUTPUT');\nwhile(true) {\n  digitalWrite('D0', 1);\n  sleep(500);\n  digitalWrite('D0', 0);\n  sleep(500);\n}"} 
              onChange={e => updateData('code', e.target.value)} 
              className="w-full text-xs font-mono border border-gray-300 rounded px-2 py-1 h-48 whitespace-pre bg-gray-50" 
              spellCheck="false"
            />
          </div>
          {selectedNode.data.logs && (selectedNode.data.logs as string[]).length > 0 && (
            <div className="mb-3 flex flex-col">
              <label className="block text-xs font-medium text-gray-700 mb-1 uppercase tracking-wider">Serial Monitor</label>
              <div className="bg-gray-900 text-green-400 font-mono text-[10px] p-2 h-32 overflow-y-auto rounded shadow-inner whitespace-pre-wrap">
                {(selectedNode.data.logs as string[]).map((log, i) => <div key={i}>{log}</div>)}
              </div>
            </div>
          )}
        </>
      )}
      {(selectedNode.type === 'npn' || selectedNode.type === 'pnp') && (
        <div className="mb-3">
          <label className="block text-xs font-medium text-gray-700 mb-1">Current Gain (BF)</label>
          <input type="number" value={(selectedNode.data.bf as number) || 300} onChange={e => updateData('bf', parseInt(e.target.value))} className="w-full text-sm border border-gray-300 rounded px-2 py-1" />
        </div>
      )}
      {(selectedNode.type === 'nmos' || selectedNode.type === 'pmos') && (
        <>
          <div className="mb-3">
            <label className="block text-xs font-medium text-gray-700 mb-1">Threshold Voltage (VTO)</label>
            <input type="number" step="0.1" value={(selectedNode.data.vto as number) || (selectedNode.type === 'nmos' ? 2.0 : -2.0)} onChange={e => updateData('vto', parseFloat(e.target.value))} className="w-full text-sm border border-gray-300 rounded px-2 py-1" />
          </div>
          <div className="mb-3">
            <label className="block text-xs font-medium text-gray-700 mb-1">Transconductance (KP)</label>
            <input type="number" step="0.01" value={(selectedNode.data.kp as number) || (selectedNode.type === 'nmos' ? 0.05 : 0.02)} onChange={e => updateData('kp', parseFloat(e.target.value))} className="w-full text-sm border border-gray-300 rounded px-2 py-1" />
          </div>
        </>
      )}
      {selectedNode.type === 'diode' && (
        <div className="mb-3">
          <label className="block text-xs font-medium text-gray-700 mb-1">Forward Voltage Drop (V)</label>
          <input type="number" step="0.1" value={(selectedNode.data.v_drop as number) || 0.7} onChange={e => updateData('v_drop', parseFloat(e.target.value))} className="w-full text-sm border border-gray-300 rounded px-2 py-1" />
          <div className="text-[10px] text-gray-400 mt-1">Silicon: 0.7V, Germanium: 0.3V</div>
        </div>
      )}
      {selectedNode.type === 'zener' && (
        <div className="mb-3">
          <label className="block text-xs font-medium text-gray-700 mb-1">Breakdown Voltage (V)</label>
          <input type="text" value={(selectedNode.data.label as string) || '5.1V'} onChange={e => updateData('label', e.target.value)} className="w-full text-sm border border-gray-300 rounded px-2 py-1" />
          <div className="text-[10px] text-gray-400 mt-1">Common: 3.3V, 5.1V, 12V</div>
        </div>
      )}
      {selectedNode.type === 'microphone' && (
        <div className="mb-3">
          <label className="block text-xs font-medium text-gray-700 mb-1">Amplification (×)</label>
          <input type="number" step="10" min="1" max="1000" value={(selectedNode.data.amplification as number) ?? 100} onChange={e => updateData('amplification', parseInt(e.target.value) || 100)} className="w-full text-sm border border-gray-300 rounded px-2 py-1" />
          <div className="text-[10px] text-gray-400 mt-1">Output voltage = mic × 0.05V × gain</div>
        </div>
      )}
      {selectedNode.type === 'speaker' && (
        <>
          <div className="mb-3">
            <label className="block text-xs font-medium text-gray-700 mb-1">Voltage Scale (V)</label>
            <input type="number" step="1" min="0.1" value={(selectedNode.data.voltageScale as number) ?? 5} onChange={e => updateData('voltageScale', parseFloat(e.target.value) || 5)} className="w-full text-sm border border-gray-300 rounded px-2 py-1" />
            <div className="text-[10px] text-gray-400 mt-1">Full-scale voltage (±V maps to ±1.0 audio)</div>
          </div>
          <div className="mb-2 flex items-center gap-2">
            <input type="checkbox" id="spk-ac" checked={!!selectedNode.data.acCouple} onChange={e => updateData('acCouple', e.target.checked)} />
            <label htmlFor="spk-ac" className="text-xs text-gray-700">AC Couple (remove DC offset)</label>
          </div>
          <div className="mb-2 flex items-center gap-2">
            <input type="checkbox" id="spk-norm" checked={!!selectedNode.data.normalize} onChange={e => updateData('normalize', e.target.checked)} />
            <label htmlFor="spk-norm" className="text-xs text-gray-700">Auto-normalize volume</label>
          </div>
        </>
      )}
      {selectedNode.type === 'scope' && (
        <>
          <div className="mb-3">
            <label className="block text-xs font-medium text-gray-700 mb-1">Y Axis Mode</label>
            <select value={(selectedNode.data.yMode as string) || 'auto'} onChange={e => updateData('yMode', e.target.value)} className="w-full text-sm border border-gray-300 rounded px-2 py-1">
              <option value="auto">Auto (Fit to Data)</option>
              <option value="fixed">Fixed Range</option>
            </select>
          </div>
          {selectedNode.data.yMode === 'fixed' && (
            <div className="grid grid-cols-2 gap-2 mb-3">
              <div>
                <label className="block text-[10px] text-gray-500 uppercase">Min (V)</label>
                <input type="number" value={(selectedNode.data.yMin as number) ?? -15} onChange={e => updateData('yMin', parseFloat(e.target.value))} className="w-full text-sm border border-gray-300 rounded px-2 py-1" />
              </div>
              <div>
                <label className="block text-[10px] text-gray-500 uppercase">Max (V)</label>
                <input type="number" value={(selectedNode.data.yMax as number) ?? 15} onChange={e => updateData('yMax', parseFloat(e.target.value))} className="w-full text-sm border border-gray-300 rounded px-2 py-1" />
              </div>
            </div>
          )}
          <div className="mb-3">
            <label className="block text-xs font-medium text-gray-700 mb-1">X Axis Mode</label>
            <select value={(selectedNode.data.xMode as string) || 'auto'} onChange={e => updateData('xMode', e.target.value)} className="w-full text-sm border border-gray-300 rounded px-2 py-1">
              <option value="auto">Auto (Full Simulation)</option>
              <option value="manual">Fixed Window</option>
            </select>
          </div>
          {selectedNode.data.xMode === 'manual' && (
            <div className="mb-3">
              <label className="block text-[10px] text-gray-500 uppercase">Time Window (ms)</label>
              <input type="number" min="1" value={(selectedNode.data.xMax as number) ?? 100} onChange={e => updateData('xMax', parseFloat(e.target.value))} className="w-full text-sm border border-gray-300 rounded px-2 py-1" />
            </div>
          )}
        </>
      )}
    </div>
  );
}

function FlowArea({ 
  nodes, edges, setNodes, onNodesChange, onEdgesChange, onConnect 
}: any) {
  const reactFlowWrapper = useRef<HTMLDivElement>(null);
  const { screenToFlowPosition } = useReactFlow();

  const onDragOver = useCallback((event: DragEvent) => {
    event.preventDefault();
    event.dataTransfer.dropEffect = 'move';
  }, []);

  const onDrop = useCallback(
    (event: DragEvent) => {
      event.preventDefault();
      const type = event.dataTransfer.getData('application/reactflow');
      const label = event.dataTransfer.getData('application/reactflow-label');

      if (typeof type === 'undefined' || !type) {
        return;
      }

      const position = screenToFlowPosition({
        x: event.clientX,
        y: event.clientY,
      });

      const newNode: Node = {
        id: `${type}-${nodeId++}`,
        type,
        position,
        data: { label, isOn: false },
      };

      setNodes((nds: Node[]) => nds.concat(newNode));
    },
    [screenToFlowPosition, setNodes]
  );

  return (
    <div className="flex-1 h-full" ref={reactFlowWrapper}>
      <ReactFlow
        nodes={nodes}
        edges={edges}
        onNodesChange={onNodesChange}
        onEdgesChange={onEdgesChange}
        onConnect={onConnect}
        onDrop={onDrop}
        onDragOver={onDragOver}
        nodeTypes={nodeTypes}
        connectionMode={ConnectionMode.Loose}
        fitView
      >
        <Background color="#ccc" gap={16} />
        <Controls />
      </ReactFlow>
    </div>
  );
}

export default function App() {
  const [nodes, setNodes] = useState<Node[]>(presets.basicBlink.nodes);
  const [edges, setEdges] = useState<Edge[]>(presets.basicBlink.edges);
  const [isSimulating, setIsSimulating] = useState(false);
  const [simLength, setSimLength] = useState(1.0);
  const [simResolution, setSimResolution] = useState<'normal' | 'high'>('normal');
  const [selectedPreset, setSelectedPreset] = useState('basicBlink');
  const [isDocsOpen, setIsDocsOpen] = useState(false);

  // Keep microphone nodes aware of the simulation duration
  useEffect(() => {
    setNodes(nds => {
      const hasMic = nds.some(n => n.type === 'microphone');
      if (!hasMic) return nds;
      return nds.map(n =>
        n.type === 'microphone' && n.data.simLength !== simLength
          ? { ...n, data: { ...n.data, simLength } }
          : n
      );
    });
  }, [simLength, setNodes]);

  const onNodesChange = useCallback(
    (changes: NodeChange[]) => setNodes((nds) => applyNodeChanges(changes, nds)),
    []
  );
  const onEdgesChange = useCallback(
    (changes: EdgeChange[]) => setEdges((eds) => applyEdgeChanges(changes, eds)),
    []
  );

  const onConnect = useCallback(
    (params: Connection) => setEdges((eds) => addEdge(params, eds)),
    []
  );

  const runSimulation = async () => {
    try {
      setIsSimulating(true);
      if (!engineInstance) {
        engineInstance = new Simulation();
        await engineInstance.start();
      }
      
      let { netlist, portToNet, mcuLogs } = generateSpiceNetlist(nodes, edges, simLength, simResolution);
      
      const mcuNodes = nodes.filter(n => n.type === 'mcu');
      const needsTwoPass = mcuNodes.some(n => {
        const code = (n.data.code as string) || "pinMode('D0', 'OUTPUT');\nwhile(true) {\n  digitalWrite('D0', 1);\n  sleep(500);\n  digitalWrite('D0', 0);\n  sleep(500);\n}";
        return code.includes('Read');
      });

      console.log("Simulating netlist (Pass 1):\n", netlist);
      
      console.log("Starting simulation...");
      engineInstance.setNetList(netlist);
      let result = await engineInstance.runSim();
      console.log("Simulation result received:", result);

      const findGraphFromSim = (res: any, netName: string) => {
        if (!netName || !res) return null;
        const search = netName.toLowerCase();
        
        // Handle eecircuit-engine format
        if (res.variableNames && res.data && res.data.length > 0 && res.data[0].values) {
          const idx = res.variableNames.findIndex((v: string) => v.toLowerCase() === search || v.toLowerCase() === `v(${search})`);
          if (idx !== -1 && res.data[idx]) {
            return {
              name: res.variableNames[idx],
              timestamps_ms: res.data[0].values.map((t: number) => t * 1000), // Time is variable 0
              voltage_levels: res.data[idx].values
            };
          }
        }
        
        return null;
      };

      if (needsTwoPass) {
         console.log("MCU needs inputs, running Pass 2...");
         const mcuWaveforms: any = {};
         for (const mcu of mcuNodes) {
           mcuWaveforms[mcu.id] = {};
           for (const pin of ['D0', 'D1', 'D2', 'D3', 'A0', 'A1']) {
             const net = portToNet[`${mcu.id}-${pin}`];
             const graph = findGraphFromSim(result, net);
             if (graph) {
               mcuWaveforms[mcu.id][pin] = graph.timestamps_ms.map((t: number, i: number) => ({
                 t, v: graph.voltage_levels[i]
               }));
             }
           }
         }
         
         const pass2 = generateSpiceNetlist(nodes, edges, simLength, simResolution, mcuWaveforms);
         netlist = pass2.netlist;
         portToNet = pass2.portToNet;
         mcuLogs = pass2.mcuLogs;
         console.log("Simulating netlist (Pass 2):\n", netlist);
         engineInstance.setNetList(netlist);
         result = await engineInstance.runSim();
      }

      const findGraph = (netName: string) => findGraphFromSim(result, netName);

      setNodes(nds => nds.map(n => {
        if (n.type === 'led') {
          const anodeNet = portToNet[`${n.id}-anode`];
          const intNet = `int_led_${n.id}`;
          
          const anodeGraph = findGraph(anodeNet);
          const intGraph = findGraph(intNet);
          
          let brightness = 0;
          let isExploded = !!n.data.isExploded;
          
          if (!isExploded && anodeGraph && intGraph) {
            // Find max current across the transient simulation
            let max_current_mA = 0;
            const current_array = [];
            for (let i = 0; i < anodeGraph.timestamps_ms.length; i++) {
               const vA = anodeGraph.voltage_levels[i];
               const vI = intGraph.voltage_levels[i];
               const current = (vA - vI) / 1.0 * 1000; // R=1 ohm, convert to mA
               current_array.push(current);
               if (current > max_current_mA) max_current_mA = current;
            }
            
            const max_allowed = Number(n.data.max_current || 20);
            if (max_current_mA > max_allowed) {
               isExploded = true;
               brightness = 0;
            } else if (max_current_mA > 0.5) {
               brightness = Math.min(1, max_current_mA / max_allowed);
            }
            
            return { ...n, data: { ...n.data, brightness, isExploded, current_array, time_points: anodeGraph.timestamps_ms } };
          }
          
          return { ...n, data: { ...n.data, brightness, isExploded } };
        }
        
        if (n.type === 'multimeter') {
          const posNet = portToNet[`${n.id}-pos`];
          const negNet = portToNet[`${n.id}-neg`];
          const posGraph = findGraph(posNet);
          const negGraph = findGraph(negNet);
          
          let voltage = 0;
          if (posGraph || negGraph) {
            const posLevels = posGraph?.voltage_levels || [];
            const negLevels = negGraph?.voltage_levels || [];
            // Get the last simulated point
            const vPos = posLevels.length > 0 ? posLevels[posLevels.length - 1] : 0;
            const vNeg = negLevels.length > 0 ? negLevels[negLevels.length - 1] : 0;
            voltage = vPos - vNeg;
          }
          return { ...n, data: { ...n.data, voltage } };
        }

        if (n.type === 'scope') {
          const ch1Net = portToNet[`${n.id}-ch1`];
          const ch2Net = portToNet[`${n.id}-ch2`];
          const gndNet = portToNet[`${n.id}-gnd`]; 
          
          const ch1Graph = findGraph(ch1Net);
          const ch2Graph = findGraph(ch2Net);
          const gndGraph = findGraph(gndNet);
          
          let voltageData1: {t: number, v: number}[] = [];
          let voltageData2: {t: number, v: number}[] = [];

          if (ch1Graph) {
             voltageData1 = ch1Graph.timestamps_ms.map((t: number, i: number) => {
               const vIn = ch1Graph.voltage_levels[i];
               const vGnd = gndGraph ? gndGraph.voltage_levels[i] : 0;
               return { t, v: vIn - vGnd };
             });
          }
          if (ch2Graph) {
             voltageData2 = ch2Graph.timestamps_ms.map((t: number, i: number) => {
               const vIn = ch2Graph.voltage_levels[i];
               const vGnd = gndGraph ? gndGraph.voltage_levels[i] : 0;
               return { t, v: vIn - vGnd };
             });
          }
          return { ...n, data: { ...n.data, voltageData1, voltageData2 } };
        }

        if (n.type === 'speaker') {
          const inNet = portToNet[`${n.id}-in`];
          const gndNet = portToNet[`${n.id}-gnd`];
          
          const inGraph = findGraph(inNet);
          const gndGraph = findGraph(gndNet);
          
          let voltageData: {t: number, v: number}[] = [];
          if (inGraph) {
             voltageData = inGraph.timestamps_ms.map((t: number, i: number) => {
               const vIn = inGraph.voltage_levels[i];
               const vGnd = gndGraph ? gndGraph.voltage_levels[i] : 0;
               return { t, v: vIn - vGnd };
             });
          }
          // Only update if there is new data to play
          if (voltageData.length > 0) {
              return { ...n, data: { ...n.data, voltageData } };
          }
        }

        if (n.type === 'mcu') {
          return { ...n, data: { ...n.data, logs: mcuLogs[n.id] } };
        }
        
        return n;
      }));
      
    } catch (e) {
      console.error("Simulation failed:", e);
      setIsSimulating(false);
    }
  };

  const stopSimulation = () => {
    setIsSimulating(false);
    setNodes(nds => nds.map(n => {
      if (n.type === 'led') {
        return { ...n, data: { ...n.data, brightness: 0, current_array: undefined, time_points: undefined } };
      }
      if (n.type === 'speaker' || n.type === 'scope') {
        return { ...n, data: { ...n.data, voltageData: undefined } };
      }
      return n;
    }));
  };

  const deleteSelected = () => {
    setNodes(nds => nds.filter(n => !n.selected));
    setEdges(eds => eds.filter(e => !e.selected));
  };

  const handlePresetChange = (e: React.ChangeEvent<HTMLSelectElement>) => {
    const key = e.target.value;
    setSelectedPreset(key);
    const preset = presets[key];
    if (preset) {
      stopSimulation();
      setNodes(preset.nodes);
      setEdges(preset.edges);
    }
  };

  return (
    <div className="flex flex-col h-screen w-full bg-gray-50 text-gray-900 font-sans overflow-hidden">
      <div className="bg-gradient-to-b from-slate-50 to-white border-b border-gray-200 px-6 py-4 flex items-center justify-between shadow-sm z-10">
        <div className="flex items-center gap-6">
          <a 
            href="https://circuit.expt.in" 
            className="flex items-center gap-3 hover:opacity-80 transition-opacity"
          >
            <Logo />
            <h1 className="text-2xl font-black text-indigo-600 tracking-tight">Circuit Expt</h1>
          </a>
          <div className="h-6 w-px bg-gray-300"></div>
          <div className="flex items-center gap-2">
            <span className="text-sm font-medium text-gray-600">Circuit:</span>
            <select
              value={selectedPreset}
              onChange={handlePresetChange}
              className="bg-gray-100 border border-gray-300 text-gray-900 text-sm rounded-md focus:ring-indigo-500 focus:border-indigo-500 block p-2"
            >
              {Object.keys(presets).map(key => (
                <option key={key} value={key}>{presets[key].name}</option>
              ))}
            </select>
          </div>
        </div>
        
        <div className="flex items-center">
          <div className="flex items-center gap-1 bg-white px-2 py-1 rounded shadow-sm border border-gray-300">
            <span className="text-xs font-semibold text-gray-700">Duration:</span>
            <input 
              type="number" 
              min="0.1" 
              step="0.1" 
              value={simLength} 
              onChange={e => setSimLength(parseFloat(e.target.value) || 1.0)} 
              className="w-16 text-sm border-none bg-transparent focus:ring-0 text-center"
            />
            <span className="text-xs text-gray-500 mr-1">s</span>
          </div>

          <div className="flex items-center gap-1 bg-white px-2 py-1 rounded shadow-sm border border-gray-300 mx-2">
            <span className="text-xs font-semibold text-gray-700">Res:</span>
            <select
              value={simResolution}
              onChange={e => setSimResolution(e.target.value as 'normal' | 'high')}
              className="bg-transparent border-none text-gray-900 text-sm focus:ring-0"
            >
              <option value="normal">Normal</option>
              <option value="high">High</option>
            </select>
          </div>
          
          <button 
            onClick={deleteSelected}
            className="flex items-center gap-2 bg-gray-500 hover:bg-gray-600 text-white px-4 py-2 rounded-md font-medium text-sm transition-colors mr-4"
          >
            <Trash2 size={16} /> Delete Selected
          </button>
          <button 
            onClick={runSimulation}
            disabled={isSimulating}
            className="flex items-center gap-2 bg-green-600 hover:bg-green-700 disabled:bg-gray-400 text-white px-4 py-2 rounded-md font-medium text-sm transition-colors"
          >
            <Play size={16} /> Simulate
          </button>
          <button 
            onClick={stopSimulation}
            disabled={!isSimulating}
            className="flex items-center gap-2 bg-red-600 hover:bg-red-700 disabled:bg-gray-400 text-white px-4 py-2 rounded-md font-medium text-sm transition-colors"
          >
            <Square size={16} /> Stop
          </button>
          <a
            href="https://github.com/tomgrek/circuitsim"
            target="_blank"
            rel="noopener noreferrer"
            className="flex items-center justify-center ml-4 w-8 h-8 rounded-full border-2 border-gray-200 text-gray-600 hover:bg-gray-50 hover:border-gray-300 transition-colors focus:outline-none"
            title="View on GitHub"
          >
            <svg xmlns="http://www.w3.org/-2000/svg" width="18" height="18" viewBox="0 0 24 24" fill="none" stroke="currentColor" strokeWidth="2" strokeLinecap="round" strokeLinejoin="round"><path d="M15 22v-4a4.8 4.8 0 0 0-1-3.5c3 0 6-2 6-5.5.08-1.25-.27-2.48-1-3.5.28-1.15.28-2.35 0-3.5 0 0-1 0-3 1.5-2.64-.5-5.36-.5-8 0C6 2 5 2 5 2c-.3 1.15-.3 2.35 0 3.5A5.403 5.403 0 0 0 4 9c0 3.5 3 5.5 6 5.5-.39.49-.68 1.05-.85 1.65-.17.6-.22 1.23-.15 1.85v4"/><path d="M9 18c-4.51 2-5-2-7-2"/></svg>
          </a>
          <button
            onClick={() => setIsDocsOpen(true)}
            className="flex items-center justify-center ml-2 w-8 h-8 rounded-full border-2 border-indigo-200 text-indigo-600 hover:bg-indigo-50 hover:border-indigo-300 transition-colors focus:outline-none"
            title="Documentation"
          >
            <Info size={18} />
          </button>
        </div>
      </div>

      <div className="flex flex-1 relative min-h-0">
        <Sidebar />
        <ReactFlowProvider>
          <FlowArea 
            nodes={nodes} edges={edges} 
            setNodes={setNodes}
            onNodesChange={onNodesChange} onEdgesChange={onEdgesChange} onConnect={onConnect}
          />
        </ReactFlowProvider>
        {nodes.find(n => n.selected) && (
           <PropertiesPanel 
             selectedNode={nodes.find(n => n.selected)!} 
             setNodes={setNodes} 
             isSimulating={isSimulating}
             runSimulation={runSimulation}
           />
        )}
        {isDocsOpen && <DocsModal onClose={() => setIsDocsOpen(false)} />}
      </div>
    </div>
  );
}
