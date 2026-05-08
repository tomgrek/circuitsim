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
import { generateSpiceNetlist } from './utils/spice';
import { Play, Square, Trash2 } from 'lucide-react';
import { createNgspiceSpiceEngine } from '@tscircuit/ngspice-spice-engine';
import { presets } from './utils/presets';

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
      {selectedNode.type === 'microphone' && (
        <div className="mb-3">
          <label className="block text-xs font-medium text-gray-700 mb-1">Amplification (×)</label>
          <input type="number" step="10" min="1" max="1000" value={(selectedNode.data.amplification as number) ?? 100} onChange={e => updateData('amplification', parseInt(e.target.value) || 100)} className="w-full text-sm border border-gray-300 rounded px-2 py-1" />
          <div className="text-[10px] text-gray-400 mt-1">Output voltage = mic × 0.05V × gain</div>
        </div>
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
        engineInstance = await createNgspiceSpiceEngine();
      }
      
      const { netlist, portToNet } = generateSpiceNetlist(nodes, edges, simLength, simResolution);
      console.log("Simulating netlist:\n", netlist);
      
      const result = await engineInstance.simulate(netlist);
      console.log("Result:", result);

      const voltageGraphs = result?.simulationResultCircuitJson?.filter(
        (r: any) => r.type === "simulation_transient_voltage_graph"
      ) || [];

      setNodes(nds => nds.map(n => {
        if (n.type === 'led') {
          const anodeNet = portToNet[`${n.id}-anode`];
          const intNet = `int_led_${n.id}`;
          
          const anodeGraph = voltageGraphs.find((g: any) => g.name.toLowerCase() === anodeNet?.toLowerCase());
          const intGraph = voltageGraphs.find((g: any) => g.name.toLowerCase() === intNet.toLowerCase());
          
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
          const posGraph = voltageGraphs.find((g: any) => g.name.toLowerCase() === posNet?.toLowerCase());
          const negGraph = voltageGraphs.find((g: any) => g.name.toLowerCase() === negNet?.toLowerCase());
          
          let voltage = 0;
          if (posGraph || negGraph) {
            // Get the last simulated point
            const vPos = posGraph ? posGraph.voltage_levels[posGraph.voltage_levels.length - 1] : 0;
            const vNeg = negGraph ? negGraph.voltage_levels[negGraph.voltage_levels.length - 1] : 0;
            voltage = vPos - vNeg;
          }
          return { ...n, data: { ...n.data, voltage } };
        }

        if (n.type === 'scope') {
          const inNet = portToNet[`${n.id}-in`];
          const gndNet = portToNet[`${n.id}-gnd`]; // often 0 if connected to ground
          
          const inGraph = voltageGraphs.find((g: any) => g.name.toLowerCase() === inNet?.toLowerCase());
          const gndGraph = voltageGraphs.find((g: any) => g.name.toLowerCase() === gndNet?.toLowerCase());
          
          let voltageData: {t: number, v: number}[] = [];
          if (inGraph) {
             voltageData = inGraph.timestamps_ms.map((t: number, i: number) => {
               const vIn = inGraph.voltage_levels[i];
               const vGnd = gndGraph ? gndGraph.voltage_levels[i] : 0;
               return { t, v: vIn - vGnd };
             });
          }
          return { ...n, data: { ...n.data, voltageData } };
        }

        if (n.type === 'speaker') {
          const inNet = portToNet[`${n.id}-in`];
          const gndNet = portToNet[`${n.id}-gnd`];
          
          const inGraph = voltageGraphs.find((g: any) => g.name.toLowerCase() === inNet?.toLowerCase());
          const gndGraph = voltageGraphs.find((g: any) => g.name.toLowerCase() === gndNet?.toLowerCase());
          
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
    <div className="flex flex-col h-screen w-full bg-gray-50 text-gray-900 font-sans">
      <div className="bg-white border-b border-gray-200 px-6 py-4 flex items-center justify-between shadow-sm z-10">
        <div className="flex items-center gap-6">
          <h1 className="text-xl font-bold text-indigo-600 tracking-tight">CircuitSim</h1>
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
        </div>
      </div>

      <div className="flex flex-1 relative h-[calc(100vh-56px)]">
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
      </div>
    </div>
  );
}
