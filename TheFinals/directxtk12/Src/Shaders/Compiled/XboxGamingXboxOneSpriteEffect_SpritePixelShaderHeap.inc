#if 0
;
; Input signature:
;
; Name                 Index   Mask Register SysValue  Format   Used
; -------------------- ----- ------ -------- -------- ------- ------
; COLOR                    0   xyzw        0     NONE   float   xyzw
; TEXCOORD                 0   xy          1     NONE   float   xy  
;
;
; Output signature:
;
; Name                 Index   Mask Register SysValue  Format   Used
; -------------------- ----- ------ -------- -------- ------- ------
; SV_Target                0   xyzw        0   TARGET   float   xyzw
;
; shader debug name: C:\Users\marcu\Downloads\DirectXTK12-main\DirectXTK12-main\Src/Shaders/Compiled\XboxGamingXboxOneSpriteEffect_SpritePixelShaderHeap.pdb
; shader hash: 6ef142db9452002103c9d5d071db0a10
;
; Pipeline Runtime Information: 
;
;PSVRuntimeInfo:
; Pixel Shader
; DepthOutput=0
; SampleFrequency=0
; MinimumExpectedWaveLaneCount: 0
; MaximumExpectedWaveLaneCount: 4294967295
; UsesViewID: false
; SigInputElements: 2
; SigOutputElements: 1
; SigPatchConstOrPrimElements: 0
; SigInputVectors: 2
; SigOutputVectors[0]: 1
; SigOutputVectors[1]: 0
; SigOutputVectors[2]: 0
; SigOutputVectors[3]: 0
; EntryFunctionName: SpritePixelShaderHeap
;
;
; Input signature:
;
; Name                 Index             InterpMode DynIdx
; -------------------- ----- ---------------------- ------
; COLOR                    0                 linear       
; TEXCOORD                 0                 linear       
;
; Output signature:
;
; Name                 Index             InterpMode DynIdx
; -------------------- ----- ---------------------- ------
; SV_Target                0                              
;
; Buffer Definitions:
;
;
; Resource Bindings:
;
; Name                                 Type  Format         Dim      ID      HLSL Bind  Count
; ------------------------------ ---------- ------- ----------- ------- -------------- ------
;                                   sampler      NA          NA      S0             s0     1
;                                   texture     f32          2d      T0             t0     1
;
;
; ViewId state:
;
; Number of inputs: 6, outputs: 4
; Outputs dependent on ViewId: {  }
; Inputs contributing to computation of Outputs:
;   output 0 depends on inputs: { 0, 4, 5 }
;   output 1 depends on inputs: { 1, 4, 5 }
;   output 2 depends on inputs: { 2, 4, 5 }
;   output 3 depends on inputs: { 3, 4, 5 }
;
target datalayout = "e-m:e-p:32:32-i1:32-i8:32-i16:32-i32:32-i64:64-f16:32-f32:32-f64:64-n8:16:32:64"
target triple = "dxil-ms-xb1"

%dx.types.Handle = type { i8* }
%dx.types.ResRet.f32 = type { float, float, float, float, i32 }
%"class.Texture2D<vector<float, 4> >" = type { <4 x float>, %"class.Texture2D<vector<float, 4> >::mips_type" }
%"class.Texture2D<vector<float, 4> >::mips_type" = type { i32 }
%struct.SamplerState = type { i32 }

define void @SpritePixelShaderHeap() {
  %1 = call %dx.types.Handle @dx.op.createHandle(i32 57, i8 0, i32 0, i32 0, i1 false)  ; CreateHandle(resourceClass,rangeId,index,nonUniformIndex)
  %2 = call %dx.types.Handle @dx.op.createHandle(i32 57, i8 3, i32 0, i32 0, i1 false)  ; CreateHandle(resourceClass,rangeId,index,nonUniformIndex)
  %3 = call float @dx.op.loadInput.f32(i32 4, i32 1, i32 0, i8 0, i32 undef)  ; LoadInput(inputSigId,rowIndex,colIndex,gsVertexAxis)
  %4 = call float @dx.op.loadInput.f32(i32 4, i32 1, i32 0, i8 1, i32 undef)  ; LoadInput(inputSigId,rowIndex,colIndex,gsVertexAxis)
  %5 = call float @dx.op.loadInput.f32(i32 4, i32 0, i32 0, i8 0, i32 undef)  ; LoadInput(inputSigId,rowIndex,colIndex,gsVertexAxis)
  %6 = call float @dx.op.loadInput.f32(i32 4, i32 0, i32 0, i8 1, i32 undef)  ; LoadInput(inputSigId,rowIndex,colIndex,gsVertexAxis)
  %7 = call float @dx.op.loadInput.f32(i32 4, i32 0, i32 0, i8 2, i32 undef)  ; LoadInput(inputSigId,rowIndex,colIndex,gsVertexAxis)
  %8 = call float @dx.op.loadInput.f32(i32 4, i32 0, i32 0, i8 3, i32 undef)  ; LoadInput(inputSigId,rowIndex,colIndex,gsVertexAxis)
  %9 = call %dx.types.ResRet.f32 @dx.op.sample.f32(i32 60, %dx.types.Handle %1, %dx.types.Handle %2, float %3, float %4, float undef, float undef, i32 0, i32 0, i32 undef, float undef)  ; Sample(srv,sampler,coord0,coord1,coord2,coord3,offset0,offset1,offset2,clamp)
  %10 = extractvalue %dx.types.ResRet.f32 %9, 0
  %11 = extractvalue %dx.types.ResRet.f32 %9, 1
  %12 = extractvalue %dx.types.ResRet.f32 %9, 2
  %13 = extractvalue %dx.types.ResRet.f32 %9, 3
  %14 = fmul fast float %10, %5
  %15 = fmul fast float %11, %6
  %16 = fmul fast float %12, %7
  %17 = fmul fast float %13, %8
  call void @dx.op.storeOutput.f32(i32 5, i32 0, i32 0, i8 0, float %14)  ; StoreOutput(outputSigId,rowIndex,colIndex,value)
  call void @dx.op.storeOutput.f32(i32 5, i32 0, i32 0, i8 1, float %15)  ; StoreOutput(outputSigId,rowIndex,colIndex,value)
  call void @dx.op.storeOutput.f32(i32 5, i32 0, i32 0, i8 2, float %16)  ; StoreOutput(outputSigId,rowIndex,colIndex,value)
  call void @dx.op.storeOutput.f32(i32 5, i32 0, i32 0, i8 3, float %17)  ; StoreOutput(outputSigId,rowIndex,colIndex,value)
  ret void
}

; Function Attrs: nounwind readnone
declare float @dx.op.loadInput.f32(i32, i32, i32, i8, i32) #0

; Function Attrs: nounwind
declare void @dx.op.storeOutput.f32(i32, i32, i32, i8, float) #1

; Function Attrs: nounwind readonly
declare %dx.types.ResRet.f32 @dx.op.sample.f32(i32, %dx.types.Handle, %dx.types.Handle, float, float, float, float, i32, i32, i32, float) #2

; Function Attrs: nounwind readonly
declare %dx.types.Handle @dx.op.createHandle(i32, i8, i32, i32, i1) #2

attributes #0 = { nounwind readnone }
attributes #1 = { nounwind }
attributes #2 = { nounwind readonly }

!xbox.compiler.options = !{!0}
!llvm.ident = !{!1}
!dx.version = !{!2}
!dx.valver = !{!3}
!dx.shaderModel = !{!4}
!dx.resources = !{!5}
!dx.viewIdState = !{!11}
!dx.entryPoints = !{!12}

!0 = !{!"__XBOX_PER_THREAD_SCRATCH_SIZE_LIMIT_IN_BYTES", !"0"}
!1 = !{!"dxcxbox 2410.2410.11116.10741"}
!2 = !{i32 1, i32 0}
!3 = !{i32 1, i32 8}
!4 = !{!"ps", i32 6, i32 0}
!5 = !{!6, null, null, !9}
!6 = !{!7}
!7 = !{i32 0, %"class.Texture2D<vector<float, 4> >"* undef, !"", i32 0, i32 0, i32 1, i32 2, i32 0, !8}
!8 = !{i32 0, i32 9}
!9 = !{!10}
!10 = !{i32 0, %struct.SamplerState* undef, !"", i32 0, i32 0, i32 1, i32 0, null}
!11 = !{[8 x i32] [i32 6, i32 4, i32 1, i32 2, i32 4, i32 8, i32 15, i32 15]}
!12 = !{void ()* @SpritePixelShaderHeap, !"SpritePixelShaderHeap", !13, !5, null}
!13 = !{!14, !20, null}
!14 = !{!15, !18}
!15 = !{i32 0, !"COLOR", i8 9, i8 0, !16, i8 2, i32 1, i8 4, i32 0, i8 0, !17}
!16 = !{i32 0}
!17 = !{i32 3, i32 15}
!18 = !{i32 1, !"TEXCOORD", i8 9, i8 0, !16, i8 2, i32 1, i8 2, i32 1, i8 0, !19}
!19 = !{i32 3, i32 3}
!20 = !{!21}
!21 = !{i32 0, !"SV_Target", i8 9, i8 16, !16, i8 0, i32 1, i8 4, i32 0, i8 0, !17}

;
; DUMPING SHADER HARDWARE INSTRUCTIONS 
;
// Shader Type               : (PS)
// Shader Hw Stage           : (PS)

// Shader Instructions:
shader main
  asic(CI)
  type(PS)
                                                            // s_ps_state in s0
  s_mov_b64     s[16:17], exec
  s_wqm_b64     exec, exec // wrscc
  s_mov_b32     s1, s7
  s_mov_b32     s2, s3
  s_mov_b32     s3, 0
  s_mov_b32     s7, 0
  s_load_dwordx8  s[8:15], s[2:3], 0x00
  s_load_dwordx4  s[4:7], s[6:7], 0x00
  s_mov_b32     m0, s1
  v_interp_p1_f32  v2, v0, attr1.x
  v_interp_p1_f32  v3, v0, attr1.y
  v_interp_p1_f32  v4, v0, attr0.x
  v_interp_p1_f32  v5, v0, attr0.y
  v_interp_p1_f32  v6, v0, attr0.z
  v_interp_p1_f32  v7, v0, attr0.w
  v_interp_p2_f32  v2, v1, attr1.x
  v_interp_p2_f32  v3, v1, attr1.y
  v_interp_p2_f32  v4, v1, attr0.x
  v_interp_p2_f32  v5, v1, attr0.y
  v_interp_p2_f32  v6, v1, attr0.z
  v_interp_p2_f32  v7, v1, attr0.w
  s_and_b64     exec, exec, s[16:17] // wrscc
  s_waitcnt     lgkmcnt(0)
  image_sample  v[0:3], v[2:3], s[8:15], s[4:7] dmask:0xf
  s_waitcnt     vmcnt(0)
  v_mul_legacy_f32  v5, v1, v5
  v_mul_legacy_f32  v2, v2, v6
  v_mul_legacy_f32  v3, v3, v7
  v_mul_legacy_f32  v4, v0, v4
  v_cvt_pkrtz_f16_f32  v0, v4, v5
  v_cvt_pkrtz_f16_f32  v1, v2, v3
  exp           mrt0, v0, v0, v1, v1 done compr vm
  s_endpgm      
end


NumVGPR=8,NumSGPR=20,LDS=0,Scratch=0,Occpancy=10


#endif

const unsigned char SpriteEffect_SpritePixelShaderHeap[] = {
  0x44, 0x58, 0x42, 0x43, 0xd3, 0xed, 0x62, 0x9a, 0x7b, 0x19, 0x9d, 0xc7,
  0x73, 0x9f, 0x59, 0xe0, 0x58, 0x4a, 0x28, 0xe8, 0x01, 0x00, 0x00, 0x00,
  0xd8, 0x0d, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00,
  0x50, 0x00, 0x00, 0x00, 0xb0, 0x00, 0x00, 0x00, 0xec, 0x00, 0x00, 0x00,
  0xec, 0x01, 0x00, 0x00, 0x70, 0x02, 0x00, 0x00, 0x04, 0x03, 0x00, 0x00,
  0x20, 0x03, 0x00, 0x00, 0x53, 0x46, 0x49, 0x30, 0x08, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x49, 0x53, 0x47, 0x31,
  0x58, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x48, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x0f, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x4e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x03, 0x03, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x43, 0x4f, 0x4c, 0x4f, 0x52, 0x00, 0x54, 0x45,
  0x58, 0x43, 0x4f, 0x4f, 0x52, 0x44, 0x00, 0x00, 0x4f, 0x53, 0x47, 0x31,
  0x34, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x40, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x53, 0x56, 0x5f, 0x54,
  0x61, 0x72, 0x67, 0x65, 0x74, 0x00, 0x00, 0x00, 0x50, 0x53, 0x56, 0x30,
  0xf8, 0x00, 0x00, 0x00, 0x34, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00,
  0x02, 0x01, 0x00, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
  0x02, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00,
  0x00, 0x43, 0x4f, 0x4c, 0x4f, 0x52, 0x00, 0x54, 0x45, 0x58, 0x43, 0x4f,
  0x4f, 0x52, 0x44, 0x00, 0x53, 0x70, 0x72, 0x69, 0x74, 0x65, 0x50, 0x69,
  0x78, 0x65, 0x6c, 0x53, 0x68, 0x61, 0x64, 0x65, 0x72, 0x48, 0x65, 0x61,
  0x70, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x10, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x01, 0x00, 0x44, 0x00, 0x03, 0x02, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x42, 0x00, 0x03, 0x02, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x44, 0x10,
  0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
  0x04, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00,
  0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x52, 0x54, 0x53, 0x30, 0x7c, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x03, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x7c, 0x00, 0x00, 0x00, 0x1d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x05, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x58, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x05, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x44, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x68, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff,
  0x49, 0x4c, 0x44, 0x4e, 0x8c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x87, 0x00,
  0x43, 0x3a, 0x5c, 0x55, 0x73, 0x65, 0x72, 0x73, 0x5c, 0x6d, 0x61, 0x72,
  0x63, 0x75, 0x5c, 0x44, 0x6f, 0x77, 0x6e, 0x6c, 0x6f, 0x61, 0x64, 0x73,
  0x5c, 0x44, 0x69, 0x72, 0x65, 0x63, 0x74, 0x58, 0x54, 0x4b, 0x31, 0x32,
  0x2d, 0x6d, 0x61, 0x69, 0x6e, 0x5c, 0x44, 0x69, 0x72, 0x65, 0x63, 0x74,
  0x58, 0x54, 0x4b, 0x31, 0x32, 0x2d, 0x6d, 0x61, 0x69, 0x6e, 0x5c, 0x53,
  0x72, 0x63, 0x2f, 0x53, 0x68, 0x61, 0x64, 0x65, 0x72, 0x73, 0x2f, 0x43,
  0x6f, 0x6d, 0x70, 0x69, 0x6c, 0x65, 0x64, 0x5c, 0x58, 0x62, 0x6f, 0x78,
  0x47, 0x61, 0x6d, 0x69, 0x6e, 0x67, 0x58, 0x62, 0x6f, 0x78, 0x4f, 0x6e,
  0x65, 0x53, 0x70, 0x72, 0x69, 0x74, 0x65, 0x45, 0x66, 0x66, 0x65, 0x63,
  0x74, 0x5f, 0x53, 0x70, 0x72, 0x69, 0x74, 0x65, 0x50, 0x69, 0x78, 0x65,
  0x6c, 0x53, 0x68, 0x61, 0x64, 0x65, 0x72, 0x48, 0x65, 0x61, 0x70, 0x2e,
  0x70, 0x64, 0x62, 0x00, 0x48, 0x41, 0x53, 0x48, 0x14, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x6e, 0xf1, 0x42, 0xdb, 0x94, 0x52, 0x00, 0x21,
  0x03, 0xc9, 0xd5, 0xd0, 0x71, 0xdb, 0x0a, 0x10, 0x44, 0x58, 0x49, 0x4c,
  0xb0, 0x0a, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0xac, 0x02, 0x00, 0x00,
  0x44, 0x58, 0x49, 0x4c, 0x00, 0x01, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x00,
  0x1c, 0x07, 0x00, 0x00, 0x58, 0x44, 0x41, 0x54, 0x06, 0x00, 0x00, 0x00,
  0x24, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x6c, 0x00, 0x00, 0x00,
  0x34, 0x07, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0xa0, 0x07, 0x00, 0x00,
  0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xb0, 0x07, 0x00, 0x00,
  0xee, 0x01, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0xa0, 0x09, 0x00, 0x00,
  0xb0, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x50, 0x0a, 0x00, 0x00,
  0x4c, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x9c, 0x0a, 0x00, 0x00,
  0x11, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0xcd, 0x01, 0x00, 0x00,
  0x44, 0x58, 0x49, 0x4c, 0x00, 0x01, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
  0x1c, 0x07, 0x00, 0x00, 0x42, 0x43, 0xc0, 0xde, 0x21, 0x0c, 0x00, 0x00,
  0xc4, 0x01, 0x00, 0x00, 0x0b, 0x82, 0x20, 0x00, 0x02, 0x00, 0x00, 0x00,
  0x13, 0x00, 0x00, 0x00, 0x07, 0x81, 0x23, 0x91, 0x41, 0xc8, 0x04, 0x49,
  0x06, 0x10, 0x32, 0x39, 0x92, 0x01, 0x84, 0x0c, 0x25, 0x05, 0x08, 0x19,
  0x1e, 0x04, 0x8b, 0x62, 0x80, 0x14, 0x45, 0x02, 0x42, 0x92, 0x0b, 0x42,
  0xa4, 0x10, 0x32, 0x14, 0x38, 0x08, 0x18, 0x4b, 0x0a, 0x32, 0x52, 0x88,
  0x48, 0x90, 0x14, 0x20, 0x43, 0x46, 0x88, 0xa5, 0x00, 0x19, 0x32, 0x42,
  0xe4, 0x48, 0x0e, 0x90, 0x91, 0x22, 0xc4, 0x50, 0x41, 0x51, 0x81, 0x8c,
  0xe1, 0x83, 0xe5, 0x8a, 0x04, 0x29, 0x46, 0x06, 0x51, 0x18, 0x00, 0x00,
  0x08, 0x00, 0x00, 0x00, 0x1b, 0x8c, 0xe0, 0xff, 0xff, 0xff, 0xff, 0x07,
  0x40, 0x02, 0xa8, 0x0d, 0x84, 0xf0, 0xff, 0xff, 0xff, 0xff, 0x03, 0x20,
  0x6d, 0x30, 0x86, 0xff, 0xff, 0xff, 0xff, 0x1f, 0x00, 0x09, 0xa8, 0x00,
  0x49, 0x18, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x13, 0x82, 0x60, 0x42,
  0x20, 0x4c, 0x08, 0x06, 0x00, 0x00, 0x00, 0x00, 0x89, 0x20, 0x00, 0x00,
  0x43, 0x00, 0x00, 0x00, 0x32, 0x22, 0x48, 0x09, 0x20, 0x64, 0x85, 0x04,
  0x93, 0x22, 0xa4, 0x84, 0x04, 0x93, 0x22, 0xe3, 0x84, 0xa1, 0x90, 0x14,
  0x12, 0x4c, 0x8a, 0x8c, 0x0b, 0x84, 0xa4, 0x4c, 0x10, 0x68, 0x23, 0x00,
  0x25, 0x00, 0x14, 0x66, 0x00, 0xe6, 0x08, 0xc0, 0x60, 0x8e, 0x00, 0x29,
  0xc6, 0x20, 0x84, 0x14, 0x42, 0xa6, 0x18, 0x80, 0x10, 0x52, 0x06, 0xa1,
  0x9b, 0x86, 0xcb, 0x9f, 0xb0, 0x87, 0x90, 0xfc, 0x95, 0x90, 0x56, 0x62,
  0xf2, 0x8b, 0xdb, 0x46, 0xc5, 0x18, 0x63, 0x10, 0x2a, 0xf7, 0x0c, 0x97,
  0x3f, 0x61, 0x0f, 0x21, 0xf9, 0x21, 0xd0, 0x0c, 0x0b, 0x81, 0x82, 0x55,
  0x18, 0x45, 0x18, 0x1b, 0x63, 0x0c, 0x42, 0xc8, 0xa0, 0x36, 0x47, 0x10,
  0x14, 0x83, 0x91, 0x42, 0xc8, 0x23, 0x38, 0x10, 0x30, 0x8c, 0x40, 0x0c,
  0x33, 0xb5, 0xc1, 0x38, 0xb0, 0x43, 0x38, 0xcc, 0xc3, 0x3c, 0xb8, 0x01,
  0x2d, 0x94, 0x03, 0x3e, 0xd0, 0x43, 0x3d, 0xc8, 0x43, 0x39, 0xc8, 0x01,
  0x29, 0xf0, 0x81, 0x3d, 0x94, 0xc3, 0x38, 0xd0, 0xc3, 0x3b, 0xc8, 0x03,
  0x1f, 0x98, 0x03, 0x3b, 0xbc, 0x43, 0x38, 0xd0, 0x03, 0x1b, 0x80, 0x01,
  0x1d, 0xf8, 0x01, 0x18, 0xf8, 0x81, 0x1e, 0xe8, 0x41, 0x3b, 0xa4, 0x03,
  0x3c, 0xcc, 0xc3, 0x2f, 0xd0, 0x43, 0x3e, 0xc0, 0x43, 0x39, 0xa0, 0x80,
  0xcc, 0x24, 0x06, 0xe3, 0xc0, 0x0e, 0xe1, 0x30, 0x0f, 0xf3, 0xe0, 0x06,
  0xb4, 0x50, 0x0e, 0xf8, 0x40, 0x0f, 0xf5, 0x20, 0x0f, 0xe5, 0x20, 0x07,
  0xa4, 0xc0, 0x07, 0xf6, 0x50, 0x0e, 0xe3, 0x40, 0x0f, 0xef, 0x20, 0x0f,
  0x7c, 0x60, 0x0e, 0xec, 0xf0, 0x0e, 0xe1, 0x40, 0x0f, 0x6c, 0x00, 0x06,
  0x74, 0xe0, 0x07, 0x60, 0xe0, 0x07, 0x48, 0x98, 0x94, 0xea, 0x4d, 0xd2,
  0x14, 0x51, 0xc2, 0xe4, 0xb3, 0x00, 0xf3, 0x2c, 0x44, 0xc4, 0x4e, 0xc0,
  0x44, 0xa0, 0x80, 0xd0, 0x4d, 0x04, 0x02, 0x00, 0x13, 0x16, 0x72, 0xc0,
  0x87, 0x74, 0x60, 0x87, 0x36, 0x68, 0x87, 0x79, 0x68, 0x03, 0x7c, 0x10,
  0x87, 0x38, 0xd8, 0xf0, 0x0a, 0xe5, 0xd0, 0x06, 0xed, 0xa0, 0x07, 0xe5,
  0xd0, 0x06, 0xf0, 0xa0, 0x07, 0x73, 0x20, 0x07, 0x7a, 0x30, 0x07, 0x72,
  0xd0, 0x06, 0xe9, 0x10, 0x07, 0x7a, 0x30, 0x07, 0x72, 0xd0, 0x06, 0xe9,
  0x80, 0x07, 0x7a, 0x30, 0x07, 0x72, 0xd0, 0x06, 0xe9, 0x10, 0x07, 0x76,
  0xa0, 0x07, 0x73, 0x20, 0x07, 0x6d, 0x90, 0x0e, 0x73, 0x20, 0x07, 0x7a,
  0x30, 0x07, 0x72, 0xd0, 0x06, 0xe9, 0x60, 0x07, 0x74, 0xa0, 0x07, 0x76,
  0x40, 0x07, 0x6d, 0x60, 0x0e, 0x71, 0x60, 0x07, 0x7a, 0x30, 0x07, 0x72,
  0xd0, 0x06, 0xe6, 0x30, 0x07, 0x72, 0xa0, 0x07, 0x73, 0x20, 0x07, 0x6d,
  0x60, 0x0e, 0x76, 0x40, 0x07, 0x7a, 0x60, 0x07, 0x74, 0xd0, 0x06, 0xee,
  0x80, 0x07, 0x7a, 0x10, 0x07, 0x76, 0xa0, 0x07, 0x73, 0x20, 0x07, 0x7a,
  0x60, 0x07, 0x74, 0x30, 0xe4, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x60, 0xc8, 0x63, 0x00, 0x01, 0x10, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x90, 0x07, 0x01, 0x02, 0x40, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x21, 0x4f, 0x03, 0x04, 0xc0,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x43, 0x1e, 0x08, 0x08,
  0x80, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xb2, 0x40, 0x00,
  0x0e, 0x00, 0x00, 0x00, 0x32, 0x1e, 0x98, 0x14, 0x19, 0x11, 0x4c, 0x90,
  0x8c, 0x09, 0x26, 0x47, 0xc6, 0x04, 0x43, 0x22, 0x25, 0x30, 0x02, 0x50,
  0x10, 0xc5, 0x50, 0x04, 0x25, 0x51, 0x06, 0xe5, 0x41, 0xa5, 0x24, 0x46,
  0x00, 0x8a, 0xa0, 0x10, 0x0a, 0x84, 0xec, 0x0c, 0x00, 0xe1, 0x19, 0x00,
  0xca, 0x63, 0x21, 0x06, 0x11, 0x08, 0x04, 0xf2, 0x3c, 0x00, 0x00, 0x00,
  0x79, 0x18, 0x00, 0x00, 0x72, 0x00, 0x00, 0x00, 0x1a, 0x03, 0x4c, 0x90,
  0x46, 0x02, 0x13, 0xc4, 0x36, 0xf8, 0xfa, 0xc2, 0x12, 0x7a, 0xc2, 0xfa,
  0x82, 0x2a, 0x92, 0xfa, 0xa2, 0x42, 0x92, 0x2a, 0x0a, 0x22, 0xfa, 0x9a,
  0x1a, 0x92, 0x0a, 0xa2, 0x1a, 0x42, 0xfa, 0x9a, 0x4a, 0xd2, 0x2a, 0xfa,
  0x62, 0x4a, 0x6a, 0x4a, 0xa2, 0xfa, 0x4a, 0x72, 0xfa, 0x12, 0xca, 0xa2,
  0x2a, 0x9a, 0x62, 0x00, 0xb3, 0x41, 0x08, 0x04, 0x76, 0x64, 0x78, 0x63,
  0x78, 0x62, 0x6f, 0x78, 0x20, 0x32, 0x34, 0x31, 0x30, 0x2e, 0x32, 0x34,
  0x31, 0x30, 0x2e, 0x31, 0x31, 0x31, 0x31, 0x36, 0x2e, 0x31, 0x30, 0x37,
  0x34, 0x31, 0x1b, 0x02, 0x62, 0x82, 0x40, 0x14, 0x13, 0x04, 0xc2, 0xd8,
  0x20, 0x18, 0xc7, 0x04, 0x81, 0x38, 0x36, 0x08, 0x46, 0x42, 0x01, 0x6e,
  0x6e, 0x82, 0x40, 0x20, 0x1b, 0x86, 0x85, 0x39, 0x26, 0x08, 0x96, 0x44,
  0x60, 0x82, 0x40, 0x24, 0x13, 0x04, 0x42, 0xd9, 0x20, 0x1c, 0xd1, 0x86,
  0xe4, 0x70, 0x9e, 0xe3, 0x30, 0xa0, 0x43, 0xda, 0x10, 0x4c, 0x13, 0x04,
  0x6c, 0xda, 0x80, 0x1c, 0xd5, 0x73, 0x1c, 0xc6, 0x01, 0x6c, 0x08, 0xac,
  0x0d, 0x04, 0x05, 0x00, 0xd7, 0x04, 0x21, 0xa3, 0x36, 0x04, 0xd9, 0x04,
  0x41, 0x00, 0x58, 0x4d, 0xc1, 0xc9, 0xa5, 0xd1, 0x95, 0x41, 0xa5, 0xe1,
  0x95, 0xb1, 0x4d, 0xa1, 0x85, 0x91, 0x95, 0xc9, 0x21, 0x95, 0x85, 0xc1,
  0xb1, 0x18, 0x7a, 0x62, 0x7a, 0x92, 0x9a, 0x20, 0x14, 0xcd, 0x04, 0xa1,
  0x70, 0x36, 0x04, 0xc7, 0x04, 0xa1, 0x78, 0x26, 0x08, 0x05, 0x34, 0x41,
  0x20, 0x96, 0x09, 0x02, 0xc1, 0x6c, 0x10, 0xc6, 0x80, 0x0c, 0x36, 0x2c,
  0x47, 0xe7, 0x7d, 0x60, 0x10, 0x06, 0x86, 0x18, 0x1c, 0x5f, 0x19, 0x10,
  0xa1, 0x2a, 0xc2, 0x1a, 0x7a, 0x7a, 0x92, 0x22, 0xda, 0x20, 0x8c, 0xc1,
  0x18, 0x6c, 0x58, 0x8c, 0x33, 0xf0, 0x3e, 0x30, 0x08, 0x03, 0x23, 0x0c,
  0x8c, 0x0f, 0x0d, 0x36, 0x08, 0x66, 0x90, 0x06, 0x4c, 0xa6, 0xac, 0xbe,
  0xa8, 0xc2, 0xe4, 0xce, 0xca, 0xe8, 0x26, 0x08, 0x45, 0xb4, 0x61, 0x39,
  0xd6, 0xc0, 0x63, 0x03, 0x30, 0xf8, 0x0c, 0x31, 0x38, 0xbe, 0x32, 0xd8,
  0x10, 0xb4, 0xc1, 0x86, 0x41, 0x0d, 0xdc, 0x00, 0xd8, 0x50, 0x6c, 0xdc,
  0x1b, 0x60, 0x40, 0x2b, 0x3c, 0xb1, 0x37, 0x3c, 0x97, 0xb1, 0xb7, 0x36,
  0xb8, 0x34, 0xb6, 0x32, 0x39, 0x97, 0x37, 0x38, 0xba, 0xb4, 0x37, 0xb7,
  0xb9, 0x29, 0x81, 0x50, 0x85, 0x8d, 0xcd, 0xae, 0xcd, 0x25, 0x8d, 0xac,
  0xcc, 0x8d, 0x6e, 0x4a, 0x40, 0x54, 0x21, 0xc3, 0x73, 0xb1, 0x2b, 0x93,
  0x9b, 0x4b, 0x7b, 0x73, 0x9b, 0x12, 0x1c, 0x4d, 0xc8, 0xf0, 0x5c, 0xec,
  0xc2, 0xd8, 0xec, 0xca, 0xe4, 0xa6, 0x04, 0x49, 0x1d, 0x32, 0x3c, 0x97,
  0x39, 0xb4, 0x30, 0xb2, 0x32, 0xb9, 0xa6, 0x37, 0xb2, 0x32, 0xb6, 0x29,
  0x01, 0x53, 0x86, 0x0c, 0xcf, 0x45, 0xae, 0x6c, 0xee, 0xad, 0x4e, 0x6e,
  0xac, 0x6c, 0x6e, 0x4a, 0x70, 0xd5, 0x21, 0xc3, 0x73, 0xb1, 0x4b, 0x2b,
  0xbb, 0x4b, 0x22, 0x9b, 0xa2, 0x0b, 0xa3, 0x2b, 0x9b, 0x12, 0x64, 0x75,
  0xc8, 0xf0, 0x5c, 0xca, 0xdc, 0xe8, 0xe4, 0xf2, 0xa0, 0xde, 0xd2, 0xdc,
  0xe8, 0xe6, 0xa6, 0x04, 0x6f, 0x00, 0x00, 0x00, 0x79, 0x18, 0x00, 0x00,
  0x4c, 0x00, 0x00, 0x00, 0x33, 0x08, 0x80, 0x1c, 0xc4, 0xe1, 0x1c, 0x66,
  0x14, 0x01, 0x3d, 0x88, 0x43, 0x38, 0x84, 0xc3, 0x8c, 0x42, 0x80, 0x07,
  0x79, 0x78, 0x07, 0x73, 0x98, 0x71, 0x0c, 0xe6, 0x00, 0x0f, 0xed, 0x10,
  0x0e, 0xf4, 0x80, 0x0e, 0x33, 0x0c, 0x42, 0x1e, 0xc2, 0xc1, 0x1d, 0xce,
  0xa1, 0x1c, 0x66, 0x30, 0x05, 0x3d, 0x88, 0x43, 0x38, 0x84, 0x83, 0x1b,
  0xcc, 0x03, 0x3d, 0xc8, 0x43, 0x3d, 0x8c, 0x03, 0x3d, 0xcc, 0x78, 0x8c,
  0x74, 0x70, 0x07, 0x7b, 0x08, 0x07, 0x79, 0x48, 0x87, 0x70, 0x70, 0x07,
  0x7a, 0x70, 0x03, 0x76, 0x78, 0x87, 0x70, 0x20, 0x87, 0x19, 0xcc, 0x11,
  0x0e, 0xec, 0x90, 0x0e, 0xe1, 0x30, 0x0f, 0x6e, 0x30, 0x0f, 0xe3, 0xf0,
  0x0e, 0xf0, 0x50, 0x0e, 0x33, 0x10, 0xc4, 0x1d, 0xde, 0x21, 0x1c, 0xd8,
  0x21, 0x1d, 0xc2, 0x61, 0x1e, 0x66, 0x30, 0x89, 0x3b, 0xbc, 0x83, 0x3b,
  0xd0, 0x43, 0x39, 0xb4, 0x03, 0x3c, 0xbc, 0x83, 0x3c, 0x84, 0x03, 0x3b,
  0xcc, 0xf0, 0x14, 0x76, 0x60, 0x07, 0x7b, 0x68, 0x07, 0x37, 0x68, 0x87,
  0x72, 0x68, 0x07, 0x37, 0x80, 0x87, 0x70, 0x90, 0x87, 0x70, 0x60, 0x07,
  0x76, 0x28, 0x07, 0x76, 0xf8, 0x05, 0x76, 0x78, 0x87, 0x77, 0x80, 0x87,
  0x5f, 0x08, 0x87, 0x71, 0x18, 0x87, 0x72, 0x98, 0x87, 0x79, 0x98, 0x81,
  0x2c, 0xee, 0xf0, 0x0e, 0xee, 0xe0, 0x0e, 0xf5, 0xc0, 0x0e, 0xec, 0x30,
  0x03, 0x62, 0xc8, 0xa1, 0x1c, 0xe4, 0xa1, 0x1c, 0xcc, 0xa1, 0x1c, 0xe4,
  0xa1, 0x1c, 0xdc, 0x61, 0x1c, 0xca, 0x21, 0x1c, 0xc4, 0x81, 0x1d, 0xca,
  0x61, 0x06, 0xd6, 0x90, 0x43, 0x39, 0xc8, 0x43, 0x39, 0x98, 0x43, 0x39,
  0xc8, 0x43, 0x39, 0xb8, 0xc3, 0x38, 0x94, 0x43, 0x38, 0x88, 0x03, 0x3b,
  0x94, 0xc3, 0x2f, 0xbc, 0x83, 0x3c, 0xfc, 0x82, 0x3b, 0xd4, 0x03, 0x3b,
  0xb0, 0xc3, 0x0c, 0xc4, 0x21, 0x07, 0x7c, 0x70, 0x03, 0x7a, 0x28, 0x87,
  0x76, 0x80, 0x87, 0x19, 0xd1, 0x43, 0x0e, 0xf8, 0xe0, 0x06, 0xe4, 0x20,
  0x0e, 0xe7, 0xe0, 0x06, 0xf6, 0x10, 0x0e, 0xf2, 0xc0, 0x0e, 0xe1, 0x90,
  0x0f, 0xef, 0x50, 0x0f, 0xf4, 0x00, 0x00, 0x00, 0x71, 0x20, 0x00, 0x00,
  0x15, 0x00, 0x00, 0x00, 0x06, 0x50, 0xb1, 0x4f, 0x84, 0x4c, 0x44, 0x8a,
  0x5c, 0xc4, 0xc2, 0x1e, 0xc0, 0x40, 0x44, 0x21, 0x01, 0x3c, 0x46, 0x20,
  0x0d, 0x97, 0xef, 0x3c, 0xbe, 0x10, 0x11, 0xc0, 0x44, 0x84, 0x40, 0x33,
  0x2c, 0x84, 0x05, 0x4c, 0xc3, 0xe5, 0x3b, 0x8f, 0xbf, 0x38, 0xc0, 0x20,
  0x36, 0x0f, 0x35, 0xf9, 0xc5, 0x6d, 0xdb, 0x00, 0x34, 0x5c, 0xbe, 0xf3,
  0xf8, 0x12, 0xc0, 0x3c, 0x0b, 0xe1, 0x17, 0xb7, 0x6d, 0x02, 0xd5, 0x70,
  0xf9, 0xce, 0xe3, 0x4b, 0x93, 0x13, 0x11, 0x28, 0x35, 0x3d, 0xd4, 0xe4,
  0x17, 0xb7, 0x0d, 0x00, 0x61, 0x20, 0x00, 0x00, 0x3b, 0x00, 0x00, 0x00,
  0x13, 0x04, 0x41, 0x2c, 0x10, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00,
  0xf4, 0x46, 0x00, 0x88, 0xcc, 0x00, 0x14, 0x42, 0x29, 0x94, 0x5c, 0xe1,
  0x51, 0x29, 0x83, 0x12, 0xa0, 0x31, 0x03, 0x00, 0x23, 0x06, 0x09, 0x00,
  0x82, 0x60, 0x00, 0x69, 0x05, 0x84, 0x61, 0xc9, 0x88, 0x41, 0x02, 0x80,
  0x20, 0x18, 0x40, 0x9b, 0x41, 0x64, 0x99, 0x32, 0x62, 0x90, 0x00, 0x20,
  0x08, 0x06, 0xc6, 0x97, 0x6c, 0x9a, 0xa4, 0x8c, 0x18, 0x24, 0x00, 0x08,
  0x82, 0x81, 0x01, 0x06, 0x0a, 0xb7, 0x15, 0xcb, 0x88, 0x41, 0x02, 0x80,
  0x20, 0x18, 0x18, 0x61, 0xb0, 0x70, 0x1c, 0xc5, 0x8c, 0x18, 0x24, 0x00,
  0x08, 0x82, 0x81, 0x21, 0x06, 0x4c, 0xd7, 0x1d, 0xcd, 0x88, 0x41, 0x02,
  0x80, 0x20, 0x18, 0x18, 0x63, 0xd0, 0x78, 0x5e, 0xe5, 0x8c, 0x18, 0x24,
  0x00, 0x08, 0x82, 0x81, 0x41, 0x06, 0xce, 0xf7, 0x29, 0xcf, 0x88, 0xc1,
  0x03, 0x80, 0x20, 0x18, 0x34, 0x63, 0xc0, 0x20, 0x87, 0x51, 0x24, 0x09,
  0x18, 0x80, 0x01, 0x94, 0x8c, 0x26, 0x04, 0xc0, 0x68, 0x82, 0x10, 0x8c,
  0x26, 0x0c, 0xc2, 0x68, 0x02, 0x31, 0x18, 0x91, 0xc8, 0xc7, 0x88, 0x44,
  0x3e, 0x46, 0x24, 0xf2, 0x31, 0x22, 0x91, 0xcf, 0x88, 0x41, 0x02, 0x80,
  0x20, 0x18, 0x20, 0x6d, 0x70, 0xa5, 0x41, 0x1a, 0x84, 0x01, 0x31, 0x62,
  0x90, 0x00, 0x20, 0x08, 0x06, 0x48, 0x1b, 0x5c, 0x69, 0x90, 0x06, 0xd3,
  0x30, 0x62, 0x90, 0x00, 0x20, 0x08, 0x06, 0x48, 0x1b, 0x5c, 0x69, 0x90,
  0x06, 0x60, 0x20, 0x8c, 0x18, 0x24, 0x00, 0x08, 0x82, 0x01, 0xd2, 0x06,
  0x57, 0x1a, 0xa4, 0x01, 0x15, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x6e, 0xf1, 0x42, 0xdb, 0x94, 0x52, 0x00, 0x21, 0x03, 0xc9, 0xd5, 0xd0,
  0x71, 0xdb, 0x0a, 0x10, 0x17, 0x00, 0x01, 0x00, 0x29, 0x04, 0x0f, 0x00,
  0x78, 0x01, 0xed, 0x97, 0xbd, 0x6e, 0x13, 0x41, 0x14, 0x85, 0xef, 0x9d,
  0x59, 0xaf, 0x7f, 0x12, 0xef, 0x3a, 0x4a, 0x40, 0x26, 0x32, 0x48, 0xa0,
  0x54, 0x54, 0x14, 0xa1, 0x23, 0x80, 0x10, 0x0f, 0x80, 0xd2, 0x11, 0x99,
  0x28, 0xca, 0x03, 0x44, 0xd0, 0x20, 0x2a, 0xb3, 0x09, 0x45, 0x52, 0xb8,
  0x48, 0x41, 0x41, 0xc9, 0x4b, 0xd0, 0xae, 0x5d, 0xa4, 0x98, 0x74, 0x34,
  0x54, 0x79, 0x89, 0x20, 0x0a, 0x40, 0x42, 0x81, 0x73, 0xc6, 0x3b, 0x64,
  0x13, 0x59, 0xd0, 0x04, 0x09, 0xc4, 0x7e, 0xd2, 0xb9, 0x77, 0xce, 0x78,
  0x66, 0x3c, 0xde, 0x6b, 0x4b, 0xd7, 0x51, 0x2a, 0x9e, 0x4f, 0x37, 0x9f,
  0x3f, 0x66, 0xfe, 0x7c, 0xf9, 0x5d, 0x7f, 0xb9, 0x2e, 0x52, 0xc3, 0x58,
  0x21, 0x66, 0xf2, 0xa6, 0xcd, 0x28, 0xb2, 0x97, 0x30, 0x8a, 0xb4, 0x18,
  0x0a, 0x1a, 0xd0, 0x02, 0x44, 0xee, 0x33, 0x14, 0x70, 0xbf, 0x48, 0x76,
  0x17, 0xba, 0xc7, 0xd1, 0x79, 0x66, 0xa1, 0x4e, 0xa1, 0xf3, 0x18, 0x68,
  0xb2, 0xff, 0x34, 0x93, 0xf2, 0x38, 0x10, 0xd6, 0x96, 0x5f, 0x0b, 0xf7,
  0x7e, 0xb2, 0xfa, 0x75, 0x05, 0xe9, 0x21, 0x24, 0x4b, 0x8f, 0x96, 0xfd,
  0x3d, 0x6e, 0xbf, 0x48, 0x38, 0xc7, 0x8c, 0xbb, 0xfd, 0xbb, 0x94, 0x3f,
  0x6f, 0x20, 0xd4, 0x89, 0x0c, 0x19, 0x7e, 0x43, 0x78, 0x4e, 0x4b, 0x45,
  0x5d, 0x43, 0x2d, 0xc7, 0xd0, 0xb4, 0xf3, 0xc9, 0x77, 0xc0, 0x3c, 0x0d,
  0xd6, 0x22, 0x96, 0x34, 0x43, 0x92, 0x58, 0xe7, 0x33, 0x7f, 0xe0, 0x7f,
  0x46, 0xf1, 0x28, 0xfd, 0xb3, 0xa0, 0xf8, 0xfd, 0x2e, 0x7e, 0x66, 0x9e,
  0x88, 0x01, 0x5c, 0x63, 0x90, 0x6c, 0x44, 0xed, 0x77, 0xe5, 0x0b, 0x5d,
  0xf0, 0x0a, 0x3f, 0x59, 0x37, 0xf1, 0x96, 0xde, 0x17, 0xab, 0xe4, 0x2d,
  0xce, 0x9a, 0x91, 0x75, 0x53, 0x37, 0xeb, 0x69, 0x0f, 0xfb, 0x51, 0x30,
  0xf8, 0x3e, 0x7c, 0xbf, 0xe4, 0xd7, 0xe0, 0xd7, 0x4a, 0x7e, 0x03, 0x7e,
  0xa3, 0xe4, 0x37, 0xe1, 0x37, 0x83, 0x0f, 0xe7, 0xa7, 0xfe, 0xfd, 0x8c,
  0xfd, 0x55, 0xad, 0xff, 0x16, 0xaa, 0x3b, 0x5e, 0x0c, 0xd5, 0x1d, 0x2f,
  0x86, 0xea, 0x8e, 0x15, 0x15, 0x15, 0x15, 0x15, 0x7f, 0x9a, 0x41, 0xb4,
  0x9f, 0x0f, 0x5a, 0x27, 0x79, 0xdd, 0x6e, 0xe7, 0xd6, 0xee, 0xe4, 0x99,
  0x7d, 0x05, 0xed, 0xe6, 0x62, 0x0f, 0xc6, 0x52, 0xdf, 0x19, 0xab, 0xfd,
  0x96, 0x4b, 0xd4, 0x70, 0x52, 0x9b, 0x75, 0xe8, 0x44, 0x9d, 0xe8, 0x82,
  0x13, 0xd3, 0x75, 0x62, 0x7b, 0x4e, 0xa3, 0xa6, 0xd3, 0x5a, 0xdb, 0xa9,
  0xcc, 0x39, 0xd5, 0x4b, 0x4e, 0xcd, 0x15, 0xa7, 0xf6, 0xaa, 0x1b, 0x74,
  0x4e, 0x76, 0x5f, 0xca, 0x70, 0x84, 0x36, 0xfe, 0xd8, 0xc8, 0x0d, 0x79,
  0x9a, 0x0e, 0x47, 0x3a, 0xd3, 0x4a, 0x4c, 0x3b, 0x4a, 0x6c, 0x1a, 0x27,
  0xd2, 0x6c, 0x24, 0xe8, 0x1b, 0xcf, 0xf4, 0x9d, 0x22, 0xdb, 0xa3, 0x45,
  0x26, 0x45, 0x53, 0x2a, 0x72, 0x8b, 0x81, 0x70, 0x4e, 0x4d, 0xc4, 0x1e,
  0xf8, 0xe7, 0x5f, 0x43, 0xce, 0x19, 0x8d, 0x11, 0x4f, 0xd7, 0x79, 0x1a,
  0x67, 0xf7, 0xf2, 0x58, 0x13, 0x4d, 0x59, 0x07, 0xde, 0x16, 0x4d, 0xf6,
  0x1d, 0xa8, 0x09, 0xc5, 0x88, 0x5d, 0x64, 0xf5, 0x1d, 0xf7, 0x84, 0x1e,
  0xa4, 0x36, 0x74, 0xe3, 0xe8, 0x75, 0xb1, 0x8a, 0x6c, 0x7d, 0x7c, 0x70,
  0xf4, 0x7a, 0x55, 0xae, 0xdb, 0xc3, 0x0f, 0xef, 0x9f, 0x1d, 0xb5, 0x3a,
  0x3f, 0x00, 0x55, 0x49, 0x7b, 0x46, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
  0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x03, 0x00, 0x08, 0x02, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x01, 0x02, 0x04, 0x02, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x01, 0x06, 0x04,
  0x04, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x00, 0x00,
  0x78, 0x01, 0x63, 0x64, 0x60, 0x60, 0x60, 0x06, 0x62, 0x09, 0x20, 0x06,
  0x81, 0x1a, 0x20, 0x96, 0x05, 0x62, 0x10, 0x60, 0x05, 0x62, 0x1b, 0x20,
  0x66, 0x02, 0x62, 0x10, 0x88, 0x00, 0x11, 0x40, 0x00, 0x12, 0x4f, 0x00,
  0x62, 0x90, 0x5e, 0x17, 0x20, 0x06, 0x01, 0x10, 0x1b, 0x06, 0xfe, 0x03,
  0x01, 0x88, 0x06, 0x01, 0x90, 0x78, 0x06, 0x10, 0x83, 0xec, 0x40, 0x55,
  0xf3, 0xff, 0x3f, 0x00, 0x59, 0xd7, 0x0a, 0x61, 0x78, 0x62, 0x6f, 0x70,
  0x01, 0x00, 0x00, 0x00, 0x7e, 0x02, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x30, 0x00, 0x00, 0x00
};
