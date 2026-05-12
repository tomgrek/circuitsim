import { useState } from 'react';
import { X } from 'lucide-react';

interface DocsModalProps {
  onClose: () => void;
}

const LICENSE_TEXT = `Circuit Expt is licensed under the MIT license. It's heavily built on ngspice, which has the following modified BSD license:

Copyright 1985 - 2018, Regents of the University of California and others

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice,
this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its
contributors may be used to endorse or promote products derived from this
software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.`;

export function DocsModal({ onClose }: DocsModalProps) {
  const [activeTab, setActiveTab] = useState<'about' | 'simulation' | 'license'>('about');

  return (
    <div className="fixed inset-0 bg-black/50 z-[100] flex items-center justify-center p-4">
      <div className="bg-white rounded-lg shadow-xl max-w-4xl w-full h-[80vh] flex flex-col overflow-hidden">
        <div className="flex items-center justify-between px-6 py-4 border-b border-gray-200">
          <h2 className="text-xl font-bold text-gray-800">Documentation</h2>
          <button onClick={onClose} className="text-gray-500 hover:text-gray-700 transition-colors">
            <X size={24} />
          </button>
        </div>
        <div className="flex flex-1 overflow-hidden">
          <div className="w-64 bg-gray-50 border-r border-gray-200 p-4 flex flex-col gap-2 overflow-y-auto">
            <button
              onClick={() => setActiveTab('about')}
              className={`text-left px-4 py-2 rounded-md font-medium transition-colors ${
                activeTab === 'about' ? 'bg-indigo-100 text-indigo-700' : 'text-gray-600 hover:bg-gray-200'
              }`}
            >
              About
            </button>
            <button
              onClick={() => setActiveTab('simulation')}
              className={`text-left px-4 py-2 rounded-md font-medium transition-colors ${
                activeTab === 'simulation' ? 'bg-indigo-100 text-indigo-700' : 'text-gray-600 hover:bg-gray-200'
              }`}
            >
              Simulation Engine
            </button>
            <button
              onClick={() => setActiveTab('license')}
              className={`text-left px-4 py-2 rounded-md font-medium transition-colors ${
                activeTab === 'license' ? 'bg-indigo-100 text-indigo-700' : 'text-gray-600 hover:bg-gray-200'
              }`}
            >
              License
            </button>
          </div>
          <div className="flex-1 p-8 overflow-y-auto">
            {activeTab === 'about' && (
              <div className="prose max-w-none text-gray-800">
                <h3 className="text-2xl font-bold mb-4">About Circuit Expt</h3>
                <p className="mb-4">
                  Circuit Expt is an interactive, browser-based electronics playground and simulation tool. 
                  It allows users to design, test, and learn about electronic circuits in real-time through a 
                  visual drag-and-drop interface.
                </p>
                <p className="mb-4">
                  Powered by the robust ngspice engine (via WebAssembly), the simulator can perform 
                  transient analysis on complex circuits involving passive components, transistors, logic 
                  gates, and even scriptable microcontrollers.
                </p>
                <p>
                  Features include:
                </p>
                <ul className="list-disc pl-6 mb-4 space-y-1">
                  <li>Real-time schematic capture and simulation</li>
                  <li>Virtual test equipment like multimeters and oscilloscopes</li>
                  <li>Dynamic, animated components (e.g. glowing LEDs)</li>
                  <li>Scriptable microcontroller nodes for mixed-signal simulation</li>
                </ul>
              </div>
            )}
            {activeTab === 'simulation' && (
              <div className="prose max-w-none text-gray-800">
                <h3 className="text-2xl font-bold mb-4">How Simulation Works</h3>
                <p className="mb-4">
                  Circuit Expt utilizes a hybrid simulation approach to seamlessly blend continuous analog components with discrete digital logic and scriptable microcontrollers. Here's how the different simulation domains operate and interact:
                </p>
                <h4 className="text-xl font-semibold mb-2 mt-6">Analog Simulation (SPICE)</h4>
                <p className="mb-4">
                  At the core is <strong>ngspice</strong>, an industry-standard open-source SPICE simulator running directly in your browser via WebAssembly. It solves the complex differential equations required to model continuous-time analog components like resistors, capacitors, inductors, diodes, and transistors with high accuracy.
                </p>
                <h4 className="text-xl font-semibold mb-2 mt-6">Digital Logic (B-Sources)</h4>
                <p className="mb-4">
                  Digital logic gates (AND, OR, NOT, etc.) are modeled using native SPICE Non-Linear Dependent Sources (B-sources) rather than external code models. This allows digital logic to natively interact with analog voltage levels. A gate reads the continuous input voltages (e.g., treating anything above 2.5V as logic HIGH) and outputs a strong 5V or 0V analog signal instantly, bridging the analog and digital worlds without complex interfacing.
                </p>
                <h4 className="text-xl font-semibold mb-2 mt-6">Microcontrollers (JavaScript)</h4>
                <p className="mb-4">
                  The MCU nodes allow you to run arbitrary JavaScript code (similar to Arduino C) in an isolated sandbox. Since ngspice cannot natively execute JS, the simulator uses a <strong>multi-pass technique</strong>:
                </p>
                <ul className="list-disc pl-6 mb-4 space-y-1">
                  <li><strong>Pass 1:</strong> The MCU's JS code is executed over the requested simulation time to record its output pin states (digital and analog waveforms).</li>
                  <li><strong>Pass 2:</strong> These recorded waveforms are injected into the SPICE netlist as Piecewise Linear (PWL) voltage sources. The full analog simulation is then run, allowing the MCU to "drive" the analog components.</li>
                </ul>
                <p>
                  If an MCU relies on analog inputs (like reading a voltage divider), the engine can perform additional simulation passes, feeding the SPICE outputs back into the JavaScript context to ensure both domains are fully synchronized!
                </p>
              </div>
            )}
            {activeTab === 'license' && (
              <div className="text-gray-800">
                <h3 className="text-2xl font-bold mb-4">License Information</h3>
                <pre className="whitespace-pre-wrap font-mono text-sm bg-gray-50 p-4 rounded border border-gray-200">
                  {LICENSE_TEXT}
                </pre>
              </div>
            )}
          </div>
        </div>
      </div>
    </div>
  );
}
