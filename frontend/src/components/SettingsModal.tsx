import { X, Settings } from 'lucide-react';

export function SettingsModal({ onClose, showAura, setShowAura }: any) {
  return (
    <div className="fixed inset-0 bg-black/50 backdrop-blur-sm z-[100] flex items-center justify-center p-4 animate-in fade-in duration-200">
      <div className="bg-white rounded-2xl shadow-2xl w-full max-w-md overflow-hidden animate-in zoom-in-95 duration-200">
        <div className="bg-gradient-to-r from-indigo-600 to-purple-600 px-6 py-4 flex items-center justify-between">
          <div className="flex items-center gap-2 text-white">
            <Settings size={20} />
            <h2 className="text-lg font-bold tracking-tight">Preferences</h2>
          </div>
          <button 
            onClick={onClose}
            className="p-1.5 hover:bg-white/20 rounded-full text-white transition-colors"
          >
            <X size={20} />
          </button>
        </div>
        
        <div className="p-6 space-y-6">
          <div className="flex items-center justify-between group">
            <div className="flex flex-col">
              <span className="text-sm font-bold text-gray-800">Electric Aura</span>
              <span className="text-xs text-gray-500">Visualize current flow in wires</span>
            </div>
            <label className="relative inline-flex items-center cursor-pointer">
              <input 
                type="checkbox" 
                checked={showAura}
                onChange={(e) => setShowAura(e.target.checked)}
                className="sr-only peer" 
              />
              <div className="w-11 h-6 bg-gray-200 peer-focus:outline-none peer-focus:ring-4 peer-focus:ring-indigo-300 rounded-full peer peer-checked:after:translate-x-full peer-checked:after:border-white after:content-[''] after:absolute after:top-[2px] after:left-[2px] after:bg-white after:border-gray-300 after:border after:rounded-full after:h-5 after:w-5 after:transition-all peer-checked:bg-indigo-600"></div>
            </label>
          </div>

          <div className="pt-4 border-t border-gray-100">
            <p className="text-[10px] text-gray-400 uppercase tracking-widest font-bold mb-2">Simulation Engine</p>
            <div className="bg-gray-50 rounded-lg p-3 text-xs text-gray-600 border border-gray-100">
              Running on <span className="font-mono font-bold text-indigo-600">ngspice-wasm</span>
            </div>
          </div>
        </div>

        <div className="bg-gray-50 px-6 py-4 flex justify-end">
          <button 
            onClick={onClose}
            className="bg-indigo-600 hover:bg-indigo-700 text-white px-5 py-2 rounded-xl font-bold text-sm shadow-lg shadow-indigo-200 transition-all active:scale-95"
          >
            Done
          </button>
        </div>
      </div>
    </div>
  );
}
