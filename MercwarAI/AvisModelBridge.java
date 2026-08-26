/* ========================================================================== */
/* AVIS SYSTEM CORE INTERFACE EXPORT                                         */
/* FILE: /avis_core/MercwarAI/AvisModelBridge.java                            */
/* DESCRIPTION: Primary JNA marshaling architecture connecting the C++ loop  */
/*              directly into the main Java execution pipeline.              */
/* ========================================================================== */

package MercwarAI;

import com.sun.jna.Library;
import com.sun.jna.Native;
import com.sun.jna.Structure;
import java.util.Arrays;
import java.util.List;

public class AvisModelBridge {

    public interface MercwarAiLib extends Library {
        public static class InferenceSessionState extends Structure {
            public long session_id;
            public int context_tokens_active;
            public float cumulative_loss_score;
            public byte strict_guardrail_enforced;

            @Override
            protected List<String> getFieldOrder() {
                return Arrays.asList("session_id", "context_tokens_active", "cumulative_loss_score", "strict_guardrail_enforced");
            }
        }

        int mercwar_ai_initialize_link(InferenceSessionState state, String config_json_path);
        int mercwar_ai_process_token_stream(InferenceSessionState state, int[] token_array, long array_length, byte[] out_response_json);
        void mercwar_ai_terminate_link(InferenceSessionState state);
    }

    public static void main(String[] args) {
        System.out.println("====================================================");
        System.out.println("   LAUNCHING NATIVE MERCWAR-AI RUNTIME LINK BINDER  ");
        System.out.println("====================================================");

        try {
            MercwarAiLib aiLib = (MercwarAiLib) Native.load("MercwarAI/libmercwar_ai.so", MercwarAiLib.class);
            MercwarAiLib.InferenceSessionState session = new MercwarAiLib.InferenceSessionState();

            int initResult = aiLib.mercwar_ai_initialize_link(session, "avis_core/config/avis_system_core.json");
            if (initResult == 0) {
                System.out.println("[JAVA SUCCESS] Core inference session registered: " + Long.toHexString(session.session_id));
                
                int[] sampleTokens = {102, 4053, 12042, 29, 0};
                byte[] responseBuffer = new byte[4096];
                
                aiLib.mercwar_ai_process_token_stream(session, sampleTokens, sampleTokens.length, responseBuffer);
                String cleanJsonOutput = new String(responseBuffer).trim();
                System.out.println("[JAVA RECEIVED] Native JSON Payload Output:\n" + cleanJsonOutput);
                
                aiLib.mercwar_ai_terminate_link(session);
            }
        } catch (UnsatisfiedLinkError e) {
            System.err.println("\n[LINK FATAL] Could not resolve libmercwar_ai.so shared binary.");
            System.err.println("Execute 'bash bootstrap_interface.sh' in the local directory first.");
        }
    }
}
