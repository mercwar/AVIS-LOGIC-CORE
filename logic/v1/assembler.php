<?php
/**
 * AVIS-LOGIC-CORE — ON-DEMAND PROGRAM ASSEMBLER
 * STACKABLE CONTEXT BUFFER INJECTION PLANE
 * ABSOLUTE DIRECTORY OPERATIONS ONLY — ZERO "cd" TRAVERSAL
 */

define('CORE_MANIFEST', 'avis/core/v4/config.json');
define('FIRE_OPEN',     '🔥==START_BLOCK==🔥');
define('FIRE_CLOSE',    '🔥==END_BLOCK==🔥');

function dispatchAssemblyBlock($absoluteSourcePath, $targetBlockName) {
    if (!file_exists($absoluteSourcePath)) {
        return "[ERROR] Source repository asset missing at path: " . $absoluteSourcePath . "\n";
    }

    $lines = file($absoluteSourcePath, FILE_IGNORE_NEW_LINES);
    $isInsideTargetBlock = false;
    $extractedBuffer = "";

    foreach ($lines as $line) {
        $trimmed = trim($line);

        // Track block isolation windows
        if (strpos($trimmed, FIRE_OPEN) !== false) {
            $isInsideTargetBlock = false; // Reset boundary tracker
            $currentBlockMeta = [];
            continue;
        }

        // Verify if this block matches the requested assistant assembly token
        if (preg_match('/^💥\s*ASSEMBLY_NODE\s*::\s*(.+)$/', $trimmed, $matches)) {
            if (trim($matches[1]) === $targetBlockName) {
                $isInsideTargetBlock = true;
                $extractedBuffer .= FIRE_OPEN . "\n" . $line . "\n";
                continue;
            }
        }

        // Capture payload string arrays while matching structural conditions
        if ($isInsideTargetBlock) {
            $extractedBuffer .= $line . "\n";
            
            if (strpos($trimmed, FIRE_CLOSE) !== false) {
                $isInsideTargetBlock = false;
                break; // Target isolated cleanly
            }
        }
    }

    return !empty($extractedBuffer) ? $extractedBuffer : "[ERROR] Assembly node execution token not found.\n";
}

// Global interface processing hook tracking incoming robot assembly parameters
// Example usage: echo dispatchAssemblyBlock("robo-knight-inventory/interpreter/stackable_assemblies.fl", "ROBO_KNIGHT_INVENTORY_C_SCANNER");
