export function Logo() {
  return (
    <svg 
      width="32" 
      height="32" 
      viewBox="0 0 100 100" 
      fill="none" 
      xmlns="http://www.w3.org/2000/svg"
      className="drop-shadow-sm"
    >
      {/* Bold, Equal-Armed X */}
      <path 
        d="M20 20L80 80M80 20L20 80" 
        stroke="#4f46e5" 
        strokeWidth="24" 
        strokeLinecap="butt"
      />
      
      {/* Signature Horizontal Waveform */}
      <path 
        d="M5 50H25L35 25L50 75L65 25L75 50H95" 
        stroke="#22d3ee" 
        strokeWidth="8" 
        strokeLinecap="round" 
        strokeLinejoin="round"
        className="drop-shadow-[0_0_8px_rgba(34,211,238,0.8)]"
      />
    </svg>
  );
}
