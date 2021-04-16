/*
 * RayLib library: rlgl.c
 * version 3.5
 *
 * Copyright 2021 Leonardo Mendez ( mlmgerencir at gmail com )
 * Copyright 2020 - 2021 Rafał Jopek ( rafaljopek at hotmail com )
 *
 */

#include "hbraylib.h"

//------------------------------------------------------------------------------------
// Shaders System Functions (Module: rlgl)
// NOTE: This functions are useless when using OpenGL 1.1
//------------------------------------------------------------------------------------

// Shader loading/unloading functions
// Shader LoadShader(const char *vsFileName, const char *fsFileName);  // Load shader from files and bind default locations
// Shader LoadShaderCode(const char *vsCode, const char *fsCode);      // Load shader from code strings and bind default locations
// void UnloadShader(Shader shader);                                   // Unload shader from GPU memory (VRAM)

// Shader GetShaderDefault(void);                                      // Get default shader
// Texture2D GetTextureDefault(void);                                  // Get default texture
// Texture2D GetShapesTexture(void);                                   // Get texture to draw shapes
// Rectangle GetShapesTextureRec(void);                                // Get texture rectangle to draw shapes
// void SetShapesTexture(Texture2D texture, Rectangle source);         // Define default texture used to draw shapes

// Shader configuration functions
// int GetShaderLocation(Shader shader, const char *uniformName);      // Get shader uniform location
// int GetShaderLocationAttrib(Shader shader, const char *attribName); // Get shader attribute location
// void SetShaderValue(Shader shader, int uniformLoc, const void *value, int uniformType);               // Set shader uniform value
// void SetShaderValueV(Shader shader, int uniformLoc, const void *value, int uniformType, int count);   // Set shader uniform value vector
// void SetShaderValueMatrix(Shader shader, int uniformLoc, Matrix mat);         // Set shader uniform value (matrix 4x4)
// void SetShaderValueTexture(Shader shader, int uniformLoc, Texture2D texture); // Set shader uniform value for texture
// void SetMatrixProjection(Matrix proj);                              // Set a custom projection matrix (replaces internal projection matrix)
// void SetMatrixModelview(Matrix view);                               // Set a custom modelview matrix (replaces internal modelview matrix)
// Matrix GetMatrixModelview(void);                                    // Get internal modelview matrix
// Matrix GetMatrixProjection(void);                                   // Get internal projection matrix

// Texture maps generation (PBR)
// NOTE: Required shaders should be provided
// TextureCubemap GenTextureCubemap(Shader shader, Texture2D panorama, int size, int format); // Generate cubemap texture from 2D panorama texture
// TextureCubemap GenTextureIrradiance(Shader shader, TextureCubemap cubemap, int size);      // Generate irradiance texture using cubemap data
// TextureCubemap GenTexturePrefilter(Shader shader, TextureCubemap cubemap, int size);       // Generate prefilter texture using cubemap data
// Texture2D GenTextureBRDF(Shader shader, int size);                  // Generate BRDF texture

// Shading begin/end functions
// void BeginShaderMode(Shader shader);                                // Begin custom shader drawing
// void EndShaderMode(void);                                           // End custom shader drawing (use default shader)
// void BeginBlendMode(int mode);                                      // Begin blending mode (alpha, additive, multiplied)
HB_FUNC( BEGINBLENDMODE )
{
   if( hb_param( 1, HB_IT_INTEGER ) != NULL )
   {
      BeginBlendMode( hb_parni( 1 ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}
// void EndBlendMode(void);               // End blending mode (reset to default: alpha blending)
HB_FUNC( ENDBLENDMODE )
{
   EndBlendMode();
}

// VR control functions
// void InitVrSimulator(void);                       // Init VR simulator for selected device parameters
// void CloseVrSimulator(void);                      // Close VR simulator for current device
// void UpdateVrTracking(Camera *camera);            // Update VR tracking (position and orientation) and camera
// void SetVrConfiguration(VrDeviceInfo info, Shader distortion);      // Set stereo rendering configuration parameters
// bool IsVrSimulatorReady(void);                    // Detect if VR simulator is ready
// void ToggleVrMode(void);                          // Enable/Disable VR experience
// void BeginVrDrawing(void);                        // Begin VR simulator stereo rendering
// void EndVrDrawing(void);                          // End VR simulator stereo rendering
