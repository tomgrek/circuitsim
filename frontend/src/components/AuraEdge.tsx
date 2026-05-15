import { BaseEdge, type EdgeProps, getSmoothStepPath } from '@xyflow/react';
import { useEffect, useState } from 'react';

export function AuraEdge({
  sourceX,
  sourceY,
  targetX,
  targetY,
  sourcePosition,
  targetPosition,
  data,
  style = {},
  markerEnd,
}: EdgeProps) {
  const [edgePath] = getSmoothStepPath({
    sourceX,
    sourceY,
    sourcePosition,
    targetPosition,
    targetX,
    targetY,
  });

  const [current, setCurrent] = useState(0);
  
  useEffect(() => {
    const currentArray = data?.current_array as number[] | undefined;
    const timePoints = data?.time_points as number[] | undefined;

    if (!currentArray || !timePoints || timePoints.length === 0) {
      setCurrent(0);
      return;
    }

    let animationFrame: number;
    let startTime = Date.now();
    const duration = timePoints[timePoints.length - 1] || 1000;

    const animate = () => {
      let elapsed = Date.now() - startTime;
      if (elapsed > duration) {
        startTime = Date.now();
        elapsed = 0;
      }

      // Find current at this time
      let idx = 0;
      for (let i = 0; i < timePoints.length; i++) {
        if (timePoints[i] >= elapsed) {
          idx = i;
          break;
        }
      }

      const I = Math.abs(currentArray[idx] || 0);
      setCurrent(I);
      
      animationFrame = requestAnimationFrame(animate);
    };

    animationFrame = requestAnimationFrame(animate);
    return () => cancelAnimationFrame(animationFrame);
  }, [data?.current_array, data?.time_points]);

  const auraClass = current > 0.004 ? 'edge-aura' : (current > 0.0001 ? 'edge-aura-faint' : '');
  
  return (
    <>
      <BaseEdge 
        path={edgePath} 
        markerEnd={markerEnd} 
        style={style} 
        className={auraClass}
      />
    </>
  );
}
