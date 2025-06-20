#if 0
;
; Input signature:
;
; Name                 Index   Mask Register SysValue  Format   Used
; -------------------- ----- ------ -------- -------- ------- ------
; SV_Position              0   xyzw        0      POS   float       
; TEXCOORD                 0   xy          1     NONE   float   xy  
;
;
; Output signature:
;
; Name                 Index   Mask Register SysValue  Format   Used
; -------------------- ----- ------ -------- -------- ------- ------
; SV_Target                0   xyzw        0   TARGET   float   xyzw
;
; shader debug name: C:\Users\marcu\Downloads\DirectXTK12-main\DirectXTK12-main\Src/Shaders/Compiled\XboxGamingXboxOneToneMap_PSReinhard_SRGB.pdb
; shader hash: 09841035000bf2282b74ce9737d842ba
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
; EntryFunctionName: PSReinhard_SRGB
;
;
; Input signature:
;
; Name                 Index             InterpMode DynIdx
; -------------------- ----- ---------------------- ------
; SV_Position              0          noperspective       
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
; cbuffer 
; {
;
;   [64 x i8] (type annotation not present)
;
; }
;
;
; Resource Bindings:
;
; Name                                 Type  Format         Dim      ID      HLSL Bind  Count
; ------------------------------ ---------- ------- ----------- ------- -------------- ------
;                                   cbuffer      NA          NA     CB0            cb0     1
;                                   sampler      NA          NA      S0             s0     1
;                                   texture     f32          2d      T0             t0     1
;
;
; ViewId state:
;
; Number of inputs: 6, outputs: 4
; Outputs dependent on ViewId: {  }
; Inputs contributing to computation of Outputs:
;   output 0 depends on inputs: { 4, 5 }
;   output 1 depends on inputs: { 4, 5 }
;   output 2 depends on inputs: { 4, 5 }
;   output 3 depends on inputs: { 4, 5 }
;
target datalayout = "e-m:e-p:32:32-i1:32-i8:32-i16:32-i32:32-i64:64-f16:32-f32:32-f64:64-n8:16:32:64"
target triple = "dxil-ms-xb1"

%dx.types.Handle = type { i8* }
%dx.types.ResRet.f32 = type { float, float, float, float, i32 }
%dx.types.CBufRet.f32 = type { float, float, float, float }
%"class.Texture2D<vector<float, 4> >" = type { <4 x float>, %"class.Texture2D<vector<float, 4> >::mips_type" }
%"class.Texture2D<vector<float, 4> >::mips_type" = type { i32 }
%hostlayout.Parameters = type { float, float, [3 x <4 x float>] }
%struct.SamplerState = type { i32 }

define void @PSReinhard_SRGB() {
  %1 = call %dx.types.Handle @dx.op.createHandle(i32 57, i8 0, i32 0, i32 0, i1 false)  ; CreateHandle(resourceClass,rangeId,index,nonUniformIndex)
  %2 = call %dx.types.Handle @dx.op.createHandle(i32 57, i8 3, i32 0, i32 0, i1 false)  ; CreateHandle(resourceClass,rangeId,index,nonUniformIndex)
  %3 = call %dx.types.Handle @dx.op.createHandle(i32 57, i8 2, i32 0, i32 0, i1 false)  ; CreateHandle(resourceClass,rangeId,index,nonUniformIndex)
  %4 = call float @dx.op.loadInput.f32(i32 4, i32 1, i32 0, i8 0, i32 undef)  ; LoadInput(inputSigId,rowIndex,colIndex,gsVertexAxis)
  %5 = call float @dx.op.loadInput.f32(i32 4, i32 1, i32 0, i8 1, i32 undef)  ; LoadInput(inputSigId,rowIndex,colIndex,gsVertexAxis)
  %6 = call %dx.types.ResRet.f32 @dx.op.sample.f32(i32 60, %dx.types.Handle %1, %dx.types.Handle %2, float %4, float %5, float undef, float undef, i32 0, i32 0, i32 undef, float undef)  ; Sample(srv,sampler,coord0,coord1,coord2,coord3,offset0,offset1,offset2,clamp)
  %7 = extractvalue %dx.types.ResRet.f32 %6, 0
  %8 = extractvalue %dx.types.ResRet.f32 %6, 1
  %9 = extractvalue %dx.types.ResRet.f32 %6, 2
  %10 = extractvalue %dx.types.ResRet.f32 %6, 3
  %11 = call %dx.types.CBufRet.f32 @dx.op.cbufferLoadLegacy.f32(i32 59, %dx.types.Handle %3, i32 0)  ; CBufferLoadLegacy(handle,regIndex)
  %12 = extractvalue %dx.types.CBufRet.f32 %11, 0
  %13 = fmul fast float %12, %7
  %14 = fmul fast float %12, %8
  %15 = fmul fast float %12, %9
  %16 = fadd fast float %13, 1.000000e+00
  %17 = fadd fast float %14, 1.000000e+00
  %18 = fadd fast float %15, 1.000000e+00
  %19 = fdiv fast float %13, %16
  %20 = fdiv fast float %14, %17
  %21 = fdiv fast float %15, %18
  %22 = call float @dx.op.unary.f32(i32 6, float %19)  ; FAbs(value)
  %23 = call float @dx.op.unary.f32(i32 6, float %20)  ; FAbs(value)
  %24 = call float @dx.op.unary.f32(i32 6, float %21)  ; FAbs(value)
  %25 = call float @dx.op.unary.f32(i32 23, float %22)  ; Log(value)
  %26 = call float @dx.op.unary.f32(i32 23, float %23)  ; Log(value)
  %27 = call float @dx.op.unary.f32(i32 23, float %24)  ; Log(value)
  %28 = fmul fast float %25, 0x3FDD1745C0000000
  %29 = fmul fast float %26, 0x3FDD1745C0000000
  %30 = fmul fast float %27, 0x3FDD1745C0000000
  %31 = call float @dx.op.unary.f32(i32 21, float %28)  ; Exp(value)
  %32 = call float @dx.op.unary.f32(i32 21, float %29)  ; Exp(value)
  %33 = call float @dx.op.unary.f32(i32 21, float %30)  ; Exp(value)
  call void @dx.op.storeOutput.f32(i32 5, i32 0, i32 0, i8 0, float %31)  ; StoreOutput(outputSigId,rowIndex,colIndex,value)
  call void @dx.op.storeOutput.f32(i32 5, i32 0, i32 0, i8 1, float %32)  ; StoreOutput(outputSigId,rowIndex,colIndex,value)
  call void @dx.op.storeOutput.f32(i32 5, i32 0, i32 0, i8 2, float %33)  ; StoreOutput(outputSigId,rowIndex,colIndex,value)
  call void @dx.op.storeOutput.f32(i32 5, i32 0, i32 0, i8 3, float %10)  ; StoreOutput(outputSigId,rowIndex,colIndex,value)
  ret void
}

; Function Attrs: nounwind readnone
declare float @dx.op.loadInput.f32(i32, i32, i32, i8, i32) #0

; Function Attrs: nounwind
declare void @dx.op.storeOutput.f32(i32, i32, i32, i8, float) #1

; Function Attrs: nounwind readonly
declare %dx.types.ResRet.f32 @dx.op.sample.f32(i32, %dx.types.Handle, %dx.types.Handle, float, float, float, float, i32, i32, i32, float) #2

; Function Attrs: nounwind readnone
declare float @dx.op.unary.f32(i32, float) #0

; Function Attrs: nounwind readonly
declare %dx.types.CBufRet.f32 @dx.op.cbufferLoadLegacy.f32(i32, %dx.types.Handle, i32) #2

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
!dx.viewIdState = !{!13}
!dx.entryPoints = !{!14}

!0 = !{!"__XBOX_PER_THREAD_SCRATCH_SIZE_LIMIT_IN_BYTES", !"0"}
!1 = !{!"dxcxbox 2410.2410.11116.10741"}
!2 = !{i32 1, i32 0}
!3 = !{i32 1, i32 8}
!4 = !{!"ps", i32 6, i32 0}
!5 = !{!6, null, !9, !11}
!6 = !{!7}
!7 = !{i32 0, %"class.Texture2D<vector<float, 4> >"* undef, !"", i32 0, i32 0, i32 1, i32 2, i32 0, !8}
!8 = !{i32 0, i32 9}
!9 = !{!10}
!10 = !{i32 0, %hostlayout.Parameters* undef, !"", i32 0, i32 0, i32 1, i32 64, null}
!11 = !{!12}
!12 = !{i32 0, %struct.SamplerState* undef, !"", i32 0, i32 0, i32 1, i32 0, null}
!13 = !{[8 x i32] [i32 6, i32 4, i32 0, i32 0, i32 0, i32 0, i32 15, i32 15]}
!14 = !{void ()* @PSReinhard_SRGB, !"PSReinhard_SRGB", !15, !5, null}
!15 = !{!16, !21, null}
!16 = !{!17, !19}
!17 = !{i32 0, !"SV_Position", i8 9, i8 3, !18, i8 4, i32 1, i8 4, i32 0, i8 0, null}
!18 = !{i32 0}
!19 = !{i32 1, !"TEXCOORD", i8 9, i8 0, !18, i8 2, i32 1, i8 2, i32 1, i8 0, !20}
!20 = !{i32 3, i32 3}
!21 = !{!22}
!22 = !{i32 0, !"SV_Target", i8 9, i8 16, !18, i8 0, i32 1, i8 4, i32 0, i8 0, !23}
!23 = !{i32 3, i32 15}

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
  s_mov_b64     s[20:21], exec
  s_wqm_b64     exec, exec // wrscc
  s_mov_b32     s2, s3
  s_mov_b32     s3, 0
  s_load_dwordx8  s[8:15], s[2:3], 0x00
  s_mov_b32     m0, s6
  v_interp_p1_f32  v2, v0, attr0.x
  v_interp_p1_f32  v3, v0, attr0.y
  s_or_b32      s1, s5, 0x00100000 // wrscc
  s_mov_b32     s0, s4
  s_mov_b32     s2, -1
  s_mov_b32     s3, 0x00024fac
  s_movk_i32    s16, 0x3092
  s_mov_b32     s17, 0x00fff000
  s_brev_b32    s18, 46
  s_brev_b32    s19, 1
  v_interp_p2_f32  v2, v1, attr0.x
  v_interp_p2_f32  v3, v1, attr0.y
  s_and_b64     exec, exec, s[20:21] // wrscc
  s_waitcnt     lgkmcnt(0)
  image_sample  v[0:3], v[2:3], s[8:15], s[16:19] dmask:0xf
  s_buffer_load_dword  s0, s[0:3], 0x00
  s_waitcnt     vmcnt(0) & lgkmcnt(0)
  v_mad_legacy_f32  v5, s0, v0, 1.0
  v_mad_legacy_f32  v6, s0, v2, 1.0
  v_mul_legacy_f32  v4, s0, v1
  v_mad_legacy_f32  v1, s0, v1, 1.0
  v_rcp_f32     v1, v1
  v_rcp_f32     v5, v5
  v_rcp_f32     v6, v6
  v_mul_legacy_f32  v2, s0, v2
  v_mul_legacy_f32  v0, s0, v0
  v_mul_legacy_f32  v0, abs(v0), abs(v5)
  v_mul_legacy_f32  v1, abs(v4), abs(v1)
  v_mul_legacy_f32  v2, abs(v2), abs(v6)
  v_log_f32     v0, v0
  v_log_f32     v1, v1
  v_log_f32     v2, v2
  v_mul_legacy_f32  v0, 0x3ee8ba2e, v0
  v_mul_legacy_f32  v1, 0x3ee8ba2e, v1
  v_mul_legacy_f32  v2, 0x3ee8ba2e, v2
  v_exp_f32     v4, v0
  v_exp_f32     v5, v1
  v_exp_f32     v2, v2
  v_cvt_pkrtz_f16_f32  v0, v4, v5
  v_cvt_pkrtz_f16_f32  v1, v2, v3
  exp           mrt0, v0, v0, v1, v1 done compr vm
  s_endpgm      
end


NumVGPR=7,NumSGPR=24,LDS=0,Scratch=0,Occpancy=10


#endif

const unsigned char ToneMap_PSReinhard_SRGB[] = {
  0x44, 0x58, 0x42, 0x43, 0xce, 0x5d, 0x5e, 0x3f, 0x10, 0x11, 0x6b, 0x68,
  0x82, 0xe3, 0x88, 0x3f, 0xc6, 0x8c, 0x33, 0xfa, 0x01, 0x00, 0x00, 0x00,
  0x6c, 0x0f, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00,
  0x50, 0x00, 0x00, 0x00, 0xb8, 0x00, 0x00, 0x00, 0xf4, 0x00, 0x00, 0x00,
  0x00, 0x02, 0x00, 0x00, 0x90, 0x02, 0x00, 0x00, 0x1c, 0x03, 0x00, 0x00,
  0x38, 0x03, 0x00, 0x00, 0x53, 0x46, 0x49, 0x30, 0x08, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x49, 0x53, 0x47, 0x31,
  0x60, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x48, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x01, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x54, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x03, 0x03, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x53, 0x56, 0x5f, 0x50, 0x6f, 0x73, 0x69, 0x74,
  0x69, 0x6f, 0x6e, 0x00, 0x54, 0x45, 0x58, 0x43, 0x4f, 0x4f, 0x52, 0x44,
  0x00, 0x00, 0x00, 0x00, 0x4f, 0x53, 0x47, 0x31, 0x34, 0x00, 0x00, 0x00,
  0x01, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00,
  0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x53, 0x56, 0x5f, 0x54, 0x61, 0x72, 0x67, 0x65,
  0x74, 0x00, 0x00, 0x00, 0x50, 0x53, 0x56, 0x30, 0x04, 0x01, 0x00, 0x00,
  0x34, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x02, 0x01, 0x00, 0x02,
  0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x0a, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
  0x18, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0d, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x54, 0x45, 0x58,
  0x43, 0x4f, 0x4f, 0x52, 0x44, 0x00, 0x50, 0x53, 0x52, 0x65, 0x69, 0x6e,
  0x68, 0x61, 0x72, 0x64, 0x5f, 0x53, 0x52, 0x47, 0x42, 0x00, 0x00, 0x00,
  0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x44, 0x03,
  0x03, 0x04, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x01, 0x01, 0x42, 0x00, 0x03, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x44, 0x10, 0x03, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x52, 0x54, 0x53, 0x30,
  0x88, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
  0x18, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x54, 0x00, 0x00, 0x00,
  0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00,
  0x30, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00,
  0x4c, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
  0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x10, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x7f, 0x7f, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x49, 0x4c, 0x44, 0x4e,
  0x84, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x00, 0x43, 0x3a, 0x5c, 0x55,
  0x73, 0x65, 0x72, 0x73, 0x5c, 0x6d, 0x61, 0x72, 0x63, 0x75, 0x5c, 0x44,
  0x6f, 0x77, 0x6e, 0x6c, 0x6f, 0x61, 0x64, 0x73, 0x5c, 0x44, 0x69, 0x72,
  0x65, 0x63, 0x74, 0x58, 0x54, 0x4b, 0x31, 0x32, 0x2d, 0x6d, 0x61, 0x69,
  0x6e, 0x5c, 0x44, 0x69, 0x72, 0x65, 0x63, 0x74, 0x58, 0x54, 0x4b, 0x31,
  0x32, 0x2d, 0x6d, 0x61, 0x69, 0x6e, 0x5c, 0x53, 0x72, 0x63, 0x2f, 0x53,
  0x68, 0x61, 0x64, 0x65, 0x72, 0x73, 0x2f, 0x43, 0x6f, 0x6d, 0x70, 0x69,
  0x6c, 0x65, 0x64, 0x5c, 0x58, 0x62, 0x6f, 0x78, 0x47, 0x61, 0x6d, 0x69,
  0x6e, 0x67, 0x58, 0x62, 0x6f, 0x78, 0x4f, 0x6e, 0x65, 0x54, 0x6f, 0x6e,
  0x65, 0x4d, 0x61, 0x70, 0x5f, 0x50, 0x53, 0x52, 0x65, 0x69, 0x6e, 0x68,
  0x61, 0x72, 0x64, 0x5f, 0x53, 0x52, 0x47, 0x42, 0x2e, 0x70, 0x64, 0x62,
  0x00, 0x00, 0x00, 0x00, 0x48, 0x41, 0x53, 0x48, 0x14, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x09, 0x84, 0x10, 0x35, 0x00, 0x0b, 0xf2, 0x28,
  0x2b, 0x74, 0xce, 0x97, 0x37, 0xd8, 0x42, 0xba, 0x44, 0x58, 0x49, 0x4c,
  0x2c, 0x0c, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x0b, 0x03, 0x00, 0x00,
  0x44, 0x58, 0x49, 0x4c, 0x00, 0x01, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x00,
  0x44, 0x08, 0x00, 0x00, 0x58, 0x44, 0x41, 0x54, 0x06, 0x00, 0x00, 0x00,
  0x24, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x6c, 0x00, 0x00, 0x00,
  0x5c, 0x08, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0xc8, 0x08, 0x00, 0x00,
  0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xd8, 0x08, 0x00, 0x00,
  0x3d, 0x02, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x18, 0x0b, 0x00, 0x00,
  0xb0, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0xc8, 0x0b, 0x00, 0x00,
  0x4f, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x18, 0x0c, 0x00, 0x00,
  0x11, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x17, 0x02, 0x00, 0x00,
  0x44, 0x58, 0x49, 0x4c, 0x00, 0x01, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
  0x44, 0x08, 0x00, 0x00, 0x42, 0x43, 0xc0, 0xde, 0x21, 0x0c, 0x00, 0x00,
  0x0e, 0x02, 0x00, 0x00, 0x0b, 0x82, 0x20, 0x00, 0x02, 0x00, 0x00, 0x00,
  0x13, 0x00, 0x00, 0x00, 0x07, 0x81, 0x23, 0x91, 0x41, 0xc8, 0x04, 0x49,
  0x06, 0x10, 0x32, 0x39, 0x92, 0x01, 0x84, 0x0c, 0x25, 0x05, 0x08, 0x19,
  0x1e, 0x04, 0x8b, 0x62, 0x80, 0x18, 0x45, 0x02, 0x42, 0x92, 0x0b, 0x42,
  0xc4, 0x10, 0x32, 0x14, 0x38, 0x08, 0x18, 0x4b, 0x0a, 0x32, 0x62, 0x88,
  0x48, 0x90, 0x14, 0x20, 0x43, 0x46, 0x88, 0xa5, 0x00, 0x19, 0x32, 0x42,
  0xe4, 0x48, 0x0e, 0x90, 0x11, 0x23, 0xc4, 0x50, 0x41, 0x51, 0x81, 0x8c,
  0xe1, 0x83, 0xe5, 0x8a, 0x04, 0x31, 0x46, 0x06, 0x51, 0x18, 0x00, 0x00,
  0x08, 0x00, 0x00, 0x00, 0x1b, 0x8c, 0xe0, 0xff, 0xff, 0xff, 0xff, 0x07,
  0x40, 0x02, 0xa8, 0x0d, 0x84, 0xf0, 0xff, 0xff, 0xff, 0xff, 0x03, 0x20,
  0x6d, 0x30, 0x86, 0xff, 0xff, 0xff, 0xff, 0x1f, 0x00, 0x09, 0xa8, 0x00,
  0x49, 0x18, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x13, 0x82, 0x60, 0x42,
  0x20, 0x4c, 0x08, 0x06, 0x00, 0x00, 0x00, 0x00, 0x89, 0x20, 0x00, 0x00,
  0x53, 0x00, 0x00, 0x00, 0x32, 0x22, 0x88, 0x09, 0x20, 0x64, 0x85, 0x04,
  0x13, 0x23, 0xa4, 0x84, 0x04, 0x13, 0x23, 0xe3, 0x84, 0xa1, 0x90, 0x14,
  0x12, 0x4c, 0x8c, 0x8c, 0x0b, 0x84, 0xc4, 0x4c, 0x10, 0x88, 0xc1, 0x08,
  0x40, 0x09, 0x00, 0x0a, 0x66, 0x00, 0xe6, 0x08, 0xc0, 0x60, 0x8e, 0x00,
  0x29, 0xc6, 0x40, 0x10, 0x44, 0x41, 0x90, 0x51, 0x0c, 0x80, 0x20, 0x88,
  0x62, 0x20, 0xe4, 0xa6, 0xe1, 0xf2, 0x27, 0xec, 0x21, 0x24, 0x7f, 0x25,
  0xa4, 0x95, 0x98, 0xfc, 0xe2, 0xb6, 0x51, 0x31, 0x0c, 0xc3, 0x40, 0x50,
  0x71, 0xcf, 0x70, 0xf9, 0x13, 0xf6, 0x10, 0x92, 0x1f, 0x02, 0xcd, 0xb0,
  0x10, 0x28, 0x58, 0x0a, 0xa3, 0x10, 0x0c, 0x33, 0x0c, 0xc3, 0x40, 0x10,
  0xc4, 0x40, 0x4d, 0x19, 0x06, 0x62, 0xa0, 0xe7, 0xa8, 0xe1, 0xf2, 0x27,
  0xec, 0x21, 0x24, 0x9f, 0xdb, 0xa8, 0x62, 0x25, 0x26, 0xbf, 0xb8, 0x6d,
  0x44, 0x0c, 0xc3, 0x30, 0x14, 0x22, 0x22, 0x18, 0x82, 0xa4, 0x39, 0x82,
  0xa0, 0x18, 0x0c, 0x51, 0x10, 0x04, 0x45, 0xd5, 0x40, 0xc0, 0x30, 0x02,
  0x31, 0xcc, 0xd4, 0x06, 0xe3, 0xc0, 0x0e, 0xe1, 0x30, 0x0f, 0xf3, 0xe0,
  0x06, 0xb4, 0x50, 0x0e, 0xf8, 0x40, 0x0f, 0xf5, 0x20, 0x0f, 0xe5, 0x20,
  0x07, 0xa4, 0xc0, 0x07, 0xf6, 0x50, 0x0e, 0xe3, 0x40, 0x0f, 0xef, 0x20,
  0x0f, 0x7c, 0x60, 0x0e, 0xec, 0xf0, 0x0e, 0xe1, 0x40, 0x0f, 0x6c, 0x00,
  0x06, 0x74, 0xe0, 0x07, 0x60, 0xe0, 0x07, 0x7a, 0xa0, 0x07, 0xed, 0x90,
  0x0e, 0xf0, 0x30, 0x0f, 0xbf, 0x40, 0x0f, 0xf9, 0x00, 0x0f, 0xe5, 0x80,
  0x02, 0x62, 0x26, 0x31, 0x18, 0x07, 0x76, 0x08, 0x87, 0x79, 0x98, 0x07,
  0x37, 0xa0, 0x85, 0x72, 0xc0, 0x07, 0x7a, 0xa8, 0x07, 0x79, 0x28, 0x07,
  0x39, 0x20, 0x05, 0x3e, 0xb0, 0x87, 0x72, 0x18, 0x07, 0x7a, 0x78, 0x07,
  0x79, 0xe0, 0x03, 0x73, 0x60, 0x87, 0x77, 0x08, 0x07, 0x7a, 0x60, 0x03,
  0x30, 0xa0, 0x03, 0x3f, 0x00, 0x03, 0x3f, 0x40, 0x02, 0x96, 0x91, 0x96,
  0x03, 0xd8, 0x55, 0x87, 0x23, 0x4d, 0x0b, 0x80, 0x39, 0xd4, 0xe4, 0xa7,
  0x40, 0x04, 0x30, 0xc4, 0x44, 0x44, 0x12, 0x1a, 0x86, 0x81, 0xa3, 0xee,
  0x26, 0x69, 0x8a, 0x28, 0x61, 0xf2, 0x59, 0x80, 0x79, 0x16, 0x22, 0x62,
  0x27, 0x60, 0x22, 0x50, 0x40, 0xd0, 0x97, 0x08, 0x04, 0x00, 0x00, 0x00,
  0x13, 0x16, 0x72, 0xc0, 0x87, 0x74, 0x60, 0x87, 0x36, 0x68, 0x87, 0x79,
  0x68, 0x03, 0x7c, 0x10, 0x87, 0x38, 0xd8, 0xf0, 0x0a, 0xe5, 0xd0, 0x06,
  0xed, 0xa0, 0x07, 0xe5, 0xd0, 0x06, 0xf0, 0xa0, 0x07, 0x73, 0x20, 0x07,
  0x7a, 0x30, 0x07, 0x72, 0xd0, 0x06, 0xe9, 0x10, 0x07, 0x7a, 0x30, 0x07,
  0x72, 0xd0, 0x06, 0xe9, 0x80, 0x07, 0x7a, 0x30, 0x07, 0x72, 0xd0, 0x06,
  0xe9, 0x10, 0x07, 0x76, 0xa0, 0x07, 0x73, 0x20, 0x07, 0x6d, 0x90, 0x0e,
  0x73, 0x20, 0x07, 0x7a, 0x30, 0x07, 0x72, 0xd0, 0x06, 0xe9, 0x60, 0x07,
  0x74, 0xa0, 0x07, 0x76, 0x40, 0x07, 0x6d, 0x60, 0x0e, 0x71, 0x60, 0x07,
  0x7a, 0x30, 0x07, 0x72, 0xd0, 0x06, 0xe6, 0x30, 0x07, 0x72, 0xa0, 0x07,
  0x73, 0x20, 0x07, 0x6d, 0x60, 0x0e, 0x76, 0x40, 0x07, 0x7a, 0x60, 0x07,
  0x74, 0xd0, 0x06, 0xee, 0x80, 0x07, 0x7a, 0x10, 0x07, 0x76, 0xa0, 0x07,
  0x73, 0x20, 0x07, 0x7a, 0x60, 0x07, 0x74, 0x30, 0xe4, 0x09, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0xc8, 0x63, 0x00,
  0x01, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x90, 0x07,
  0x01, 0x02, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x21,
  0x4f, 0x03, 0x04, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x43, 0x9e, 0x07, 0x08, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x86, 0x3c, 0x12, 0x10, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x0c, 0x79, 0x2a, 0x20, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xc8, 0x02, 0x01, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
  0x32, 0x1e, 0x98, 0x14, 0x19, 0x11, 0x4c, 0x90, 0x8c, 0x09, 0x26, 0x47,
  0xc6, 0x04, 0x43, 0x22, 0x4a, 0x60, 0x04, 0xa0, 0x20, 0x8a, 0xa1, 0x08,
  0x4a, 0xa2, 0x00, 0x03, 0xca, 0xa0, 0x3c, 0xa8, 0x28, 0x89, 0x32, 0x28,
  0x84, 0x11, 0x80, 0x22, 0x28, 0x10, 0xda, 0x66, 0x00, 0xc8, 0x9b, 0x01,
  0x20, 0x70, 0x06, 0x80, 0xc2, 0xb1, 0x10, 0x83, 0x00, 0x00, 0x00, 0x78,
  0x1e, 0x00, 0x00, 0x00, 0x79, 0x18, 0x00, 0x00, 0x79, 0x00, 0x00, 0x00,
  0x1a, 0x03, 0x4c, 0x90, 0x46, 0x02, 0x13, 0xc4, 0x36, 0xf8, 0xfa, 0xc2,
  0x12, 0x7a, 0xc2, 0xfa, 0x82, 0x2a, 0x92, 0xfa, 0xa2, 0x42, 0x92, 0x2a,
  0x0a, 0x22, 0xfa, 0x9a, 0x1a, 0x92, 0x0a, 0xa2, 0x1a, 0x42, 0xfa, 0x9a,
  0x4a, 0xd2, 0x2a, 0xfa, 0x62, 0x4a, 0x6a, 0x4a, 0xa2, 0xfa, 0x4a, 0x72,
  0xfa, 0x12, 0xca, 0xa2, 0x2a, 0x9a, 0x62, 0x00, 0xb3, 0x41, 0x08, 0x04,
  0x76, 0x64, 0x78, 0x63, 0x78, 0x62, 0x6f, 0x78, 0x20, 0x32, 0x34, 0x31,
  0x30, 0x2e, 0x32, 0x34, 0x31, 0x30, 0x2e, 0x31, 0x31, 0x31, 0x31, 0x36,
  0x2e, 0x31, 0x30, 0x37, 0x34, 0x31, 0x1b, 0x02, 0x62, 0x82, 0x40, 0x1c,
  0x13, 0x04, 0x02, 0xd9, 0x20, 0x18, 0xc7, 0x04, 0x81, 0x48, 0x36, 0x08,
  0x46, 0x42, 0x01, 0x6e, 0x6e, 0x82, 0x40, 0x28, 0x1b, 0x86, 0x85, 0x39,
  0x26, 0x08, 0x9b, 0x45, 0x60, 0x82, 0x40, 0x2c, 0x13, 0x04, 0x82, 0xd9,
  0x20, 0x1c, 0xd1, 0x86, 0xe4, 0x70, 0x9e, 0xe3, 0x30, 0xa0, 0x43, 0xda,
  0x10, 0x4c, 0x13, 0x04, 0xef, 0x9a, 0x20, 0x10, 0xcd, 0x06, 0xe4, 0xa8,
  0x9e, 0xe3, 0x30, 0x2c, 0x60, 0x43, 0x70, 0x4d, 0x10, 0xc0, 0x00, 0xdb,
  0x80, 0x1c, 0xd9, 0x73, 0x1c, 0xc6, 0x01, 0x6c, 0x08, 0xb4, 0x0d, 0x04,
  0x05, 0x60, 0xdb, 0x04, 0x21, 0x0c, 0xb2, 0x0d, 0x41, 0x37, 0x41, 0x10,
  0x00, 0x3e, 0x50, 0x53, 0x52, 0x65, 0x69, 0x6e, 0x68, 0x61, 0x72, 0x64,
  0x5f, 0x53, 0x52, 0x47, 0x42, 0x5c, 0xa6, 0xac, 0xbe, 0xa0, 0xde, 0xe6,
  0xd2, 0xe8, 0xd2, 0xde, 0xdc, 0x26, 0x08, 0x05, 0x34, 0x41, 0x28, 0xa2,
  0x0d, 0xc1, 0x31, 0x41, 0x28, 0xa4, 0x09, 0x42, 0x31, 0x6d, 0x58, 0x8e,
  0x30, 0x10, 0x83, 0x31, 0x20, 0x83, 0x32, 0x30, 0xca, 0xe0, 0x30, 0x03,
  0x80, 0x08, 0x55, 0x11, 0xd6, 0xd0, 0xd3, 0x93, 0x14, 0xd1, 0x04, 0xa1,
  0xa0, 0x26, 0x08, 0x84, 0xb3, 0x41, 0x50, 0x03, 0x35, 0xd8, 0xb0, 0x18,
  0x68, 0x20, 0x06, 0x66, 0x40, 0x06, 0x69, 0x60, 0xa4, 0x81, 0x61, 0x06,
  0x6b, 0xb0, 0x41, 0x38, 0x03, 0x36, 0x60, 0x32, 0x65, 0xf5, 0x45, 0x15,
  0x26, 0x77, 0x56, 0x46, 0x37, 0x41, 0x28, 0xaa, 0x09, 0x02, 0xf1, 0x6c,
  0x10, 0xd4, 0x00, 0x0e, 0x36, 0x2c, 0x87, 0x1b, 0x88, 0xc1, 0x1b, 0x90,
  0x81, 0x19, 0x18, 0x65, 0x70, 0x98, 0x41, 0x1c, 0x6c, 0x08, 0xe4, 0x60,
  0xc3, 0xd0, 0x06, 0x73, 0x00, 0x6c, 0x28, 0x3e, 0x30, 0xa0, 0x03, 0x0e,
  0x68, 0x85, 0x27, 0xf6, 0x86, 0xe7, 0x32, 0xf6, 0xd6, 0x06, 0x97, 0xc6,
  0x56, 0x26, 0xe7, 0xf2, 0x06, 0x47, 0x97, 0xf6, 0xe6, 0x36, 0x37, 0x25,
  0x10, 0xaa, 0xb0, 0xb1, 0xd9, 0xb5, 0xb9, 0xa4, 0x91, 0x95, 0xb9, 0xd1,
  0x4d, 0x09, 0x88, 0x2a, 0x64, 0x78, 0x2e, 0x76, 0x65, 0x72, 0x73, 0x69,
  0x6f, 0x6e, 0x53, 0x82, 0xa3, 0x09, 0x19, 0x9e, 0x8b, 0x5d, 0x18, 0x9b,
  0x5d, 0x99, 0xdc, 0x94, 0x20, 0xa9, 0x43, 0x86, 0xe7, 0x32, 0x87, 0x16,
  0x46, 0x56, 0x26, 0xd7, 0xf4, 0x46, 0x56, 0xc6, 0x36, 0x25, 0x60, 0xca,
  0x90, 0xe1, 0xb9, 0xc8, 0x95, 0xcd, 0xbd, 0xd5, 0xc9, 0x8d, 0x95, 0xcd,
  0x4d, 0x09, 0xb6, 0x3a, 0x64, 0x78, 0x2e, 0x76, 0x69, 0x65, 0x77, 0x49,
  0x64, 0x53, 0x74, 0x61, 0x74, 0x65, 0x53, 0x82, 0xae, 0x0e, 0x19, 0x9e,
  0x4b, 0x99, 0x1b, 0x9d, 0x5c, 0x1e, 0xd4, 0x5b, 0x9a, 0x1b, 0xdd, 0xdc,
  0x94, 0x80, 0x0e, 0x00, 0x79, 0x18, 0x00, 0x00, 0x4c, 0x00, 0x00, 0x00,
  0x33, 0x08, 0x80, 0x1c, 0xc4, 0xe1, 0x1c, 0x66, 0x14, 0x01, 0x3d, 0x88,
  0x43, 0x38, 0x84, 0xc3, 0x8c, 0x42, 0x80, 0x07, 0x79, 0x78, 0x07, 0x73,
  0x98, 0x71, 0x0c, 0xe6, 0x00, 0x0f, 0xed, 0x10, 0x0e, 0xf4, 0x80, 0x0e,
  0x33, 0x0c, 0x42, 0x1e, 0xc2, 0xc1, 0x1d, 0xce, 0xa1, 0x1c, 0x66, 0x30,
  0x05, 0x3d, 0x88, 0x43, 0x38, 0x84, 0x83, 0x1b, 0xcc, 0x03, 0x3d, 0xc8,
  0x43, 0x3d, 0x8c, 0x03, 0x3d, 0xcc, 0x78, 0x8c, 0x74, 0x70, 0x07, 0x7b,
  0x08, 0x07, 0x79, 0x48, 0x87, 0x70, 0x70, 0x07, 0x7a, 0x70, 0x03, 0x76,
  0x78, 0x87, 0x70, 0x20, 0x87, 0x19, 0xcc, 0x11, 0x0e, 0xec, 0x90, 0x0e,
  0xe1, 0x30, 0x0f, 0x6e, 0x30, 0x0f, 0xe3, 0xf0, 0x0e, 0xf0, 0x50, 0x0e,
  0x33, 0x10, 0xc4, 0x1d, 0xde, 0x21, 0x1c, 0xd8, 0x21, 0x1d, 0xc2, 0x61,
  0x1e, 0x66, 0x30, 0x89, 0x3b, 0xbc, 0x83, 0x3b, 0xd0, 0x43, 0x39, 0xb4,
  0x03, 0x3c, 0xbc, 0x83, 0x3c, 0x84, 0x03, 0x3b, 0xcc, 0xf0, 0x14, 0x76,
  0x60, 0x07, 0x7b, 0x68, 0x07, 0x37, 0x68, 0x87, 0x72, 0x68, 0x07, 0x37,
  0x80, 0x87, 0x70, 0x90, 0x87, 0x70, 0x60, 0x07, 0x76, 0x28, 0x07, 0x76,
  0xf8, 0x05, 0x76, 0x78, 0x87, 0x77, 0x80, 0x87, 0x5f, 0x08, 0x87, 0x71,
  0x18, 0x87, 0x72, 0x98, 0x87, 0x79, 0x98, 0x81, 0x2c, 0xee, 0xf0, 0x0e,
  0xee, 0xe0, 0x0e, 0xf5, 0xc0, 0x0e, 0xec, 0x30, 0x03, 0x62, 0xc8, 0xa1,
  0x1c, 0xe4, 0xa1, 0x1c, 0xcc, 0xa1, 0x1c, 0xe4, 0xa1, 0x1c, 0xdc, 0x61,
  0x1c, 0xca, 0x21, 0x1c, 0xc4, 0x81, 0x1d, 0xca, 0x61, 0x06, 0xd6, 0x90,
  0x43, 0x39, 0xc8, 0x43, 0x39, 0x98, 0x43, 0x39, 0xc8, 0x43, 0x39, 0xb8,
  0xc3, 0x38, 0x94, 0x43, 0x38, 0x88, 0x03, 0x3b, 0x94, 0xc3, 0x2f, 0xbc,
  0x83, 0x3c, 0xfc, 0x82, 0x3b, 0xd4, 0x03, 0x3b, 0xb0, 0xc3, 0x0c, 0xc4,
  0x21, 0x07, 0x7c, 0x70, 0x03, 0x7a, 0x28, 0x87, 0x76, 0x80, 0x87, 0x19,
  0xd1, 0x43, 0x0e, 0xf8, 0xe0, 0x06, 0xe4, 0x20, 0x0e, 0xe7, 0xe0, 0x06,
  0xf6, 0x10, 0x0e, 0xf2, 0xc0, 0x0e, 0xe1, 0x90, 0x0f, 0xef, 0x50, 0x0f,
  0xf4, 0x00, 0x00, 0x00, 0x71, 0x20, 0x00, 0x00, 0x1d, 0x00, 0x00, 0x00,
  0x06, 0xf0, 0xa4, 0xec, 0x4a, 0x20, 0xcd, 0x01, 0x44, 0xc3, 0xcf, 0xae,
  0xe0, 0x66, 0x05, 0xdb, 0x70, 0xf9, 0xce, 0xe3, 0x0b, 0x01, 0x55, 0x14,
  0x44, 0x54, 0x3a, 0xc0, 0x50, 0x12, 0x06, 0x20, 0x60, 0x7e, 0x71, 0xdb,
  0x66, 0x20, 0x0d, 0x97, 0xef, 0x3c, 0xbe, 0x10, 0x11, 0xc0, 0x44, 0x84,
  0x40, 0x33, 0x2c, 0x84, 0x05, 0x4c, 0xc3, 0xe5, 0x3b, 0x8f, 0xbf, 0x38,
  0xc0, 0x20, 0x36, 0x0f, 0x35, 0xf9, 0xc5, 0x6d, 0xdb, 0x00, 0x34, 0x5c,
  0xbe, 0xf3, 0xf8, 0x12, 0xc0, 0x3c, 0x0b, 0xe1, 0x17, 0xb7, 0x6d, 0x02,
  0xd5, 0x70, 0xf9, 0xce, 0xe3, 0x4b, 0x93, 0x13, 0x11, 0x28, 0x35, 0x3d,
  0xd4, 0xe4, 0x17, 0xb7, 0x6d, 0x04, 0xcf, 0x70, 0xf9, 0xce, 0xe3, 0x53,
  0x0d, 0x10, 0x61, 0x7e, 0x71, 0xdb, 0x00, 0x00, 0x61, 0x20, 0x00, 0x00,
  0x5d, 0x00, 0x00, 0x00, 0x13, 0x04, 0x41, 0x2c, 0x10, 0x00, 0x00, 0x00,
  0x0a, 0x00, 0x00, 0x00, 0x44, 0x8d, 0x00, 0x50, 0x51, 0x02, 0x44, 0x94,
  0x5d, 0x29, 0x94, 0xdc, 0x0c, 0x40, 0xb9, 0x94, 0x4a, 0x21, 0x14, 0x1e,
  0x0d, 0x63, 0x04, 0x6e, 0xec, 0xc6, 0xee, 0x37, 0x46, 0x00, 0x82, 0x20,
  0x88, 0x7f, 0x33, 0x00, 0x00, 0x00, 0x00, 0x00, 0x23, 0x06, 0x09, 0x00,
  0x82, 0x60, 0x50, 0x85, 0x41, 0x42, 0x7d, 0x5f, 0x33, 0x62, 0x90, 0x00,
  0x20, 0x08, 0x06, 0x95, 0x18, 0x28, 0x17, 0x18, 0x80, 0x81, 0x33, 0x62,
  0x90, 0x00, 0x20, 0x08, 0x06, 0xd5, 0x18, 0x2c, 0x55, 0x18, 0x84, 0xc1,
  0x33, 0x62, 0x90, 0x00, 0x20, 0x08, 0x06, 0x46, 0x1a, 0x20, 0x63, 0x20,
  0x06, 0xd7, 0x32, 0x62, 0x90, 0x00, 0x20, 0x08, 0x06, 0x86, 0x1a, 0x24,
  0x64, 0x30, 0x06, 0x10, 0x33, 0x62, 0xf0, 0x00, 0x20, 0x08, 0x06, 0x4d,
  0x1a, 0x24, 0x05, 0x21, 0x04, 0x86, 0x41, 0x06, 0x64, 0xd0, 0x18, 0xa3,
  0x09, 0x01, 0x30, 0x9a, 0x20, 0x04, 0xa3, 0x09, 0x83, 0x30, 0x9a, 0x40,
  0x0c, 0x23, 0x06, 0x07, 0x00, 0x82, 0x60, 0x20, 0xb1, 0x41, 0x85, 0xa4,
  0xc1, 0x68, 0x42, 0x00, 0x58, 0x60, 0xc8, 0xc7, 0x04, 0x43, 0x3e, 0x36,
  0x18, 0xf2, 0xb1, 0x21, 0x82, 0x8f, 0x0d, 0x12, 0x7c, 0x6c, 0x98, 0xe0,
  0x63, 0xc6, 0x40, 0x1f, 0x33, 0x06, 0xfa, 0x98, 0x31, 0xd0, 0x67, 0xc4,
  0xc0, 0x00, 0x40, 0x10, 0x0c, 0x1e, 0x3c, 0x90, 0x83, 0x61, 0xc4, 0xc0,
  0x00, 0x40, 0x10, 0x0c, 0x9e, 0x3c, 0x98, 0x83, 0x61, 0xc4, 0xc0, 0x00,
  0x40, 0x10, 0x0c, 0x1e, 0x3d, 0xa0, 0x83, 0x61, 0xc4, 0xc0, 0x00, 0x40,
  0x10, 0x0c, 0x9e, 0x3d, 0xf8, 0x86, 0x11, 0x03, 0x03, 0x00, 0x41, 0x30,
  0x78, 0xf8, 0x00, 0x0c, 0x86, 0x11, 0x03, 0x03, 0x00, 0x41, 0x30, 0x78,
  0xfa, 0x20, 0x0c, 0x06, 0x1b, 0x3c, 0xf9, 0xd8, 0xf0, 0xc9, 0xc7, 0x06,
  0x30, 0x90, 0xcf, 0x88, 0x81, 0x01, 0x80, 0x20, 0x18, 0x3c, 0xa1, 0x40,
  0x06, 0xc3, 0x88, 0x81, 0x01, 0x80, 0x20, 0x18, 0x3c, 0xa2, 0x50, 0x06,
  0xc3, 0x88, 0x81, 0x01, 0x80, 0x20, 0x18, 0x3c, 0xa3, 0x60, 0x06, 0xc3,
  0x88, 0x41, 0x02, 0x80, 0x20, 0x18, 0x20, 0xa6, 0xb0, 0x06, 0xa0, 0x00,
  0x0a, 0x75, 0x30, 0x8c, 0x18, 0x24, 0x00, 0x08, 0x82, 0x01, 0x62, 0x0a,
  0x6b, 0x00, 0x0a, 0xa0, 0xd0, 0x06, 0xc2, 0x88, 0x41, 0x02, 0x80, 0x20,
  0x18, 0x20, 0xa6, 0xb0, 0x06, 0xa0, 0x00, 0x0a, 0x74, 0x10, 0x8c, 0x18,
  0x24, 0x00, 0x08, 0x82, 0x01, 0x62, 0x0a, 0x6b, 0x00, 0x0a, 0xa0, 0x70,
  0x07, 0x18, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x84, 0x10, 0x35,
  0x00, 0x0b, 0xf2, 0x28, 0x2b, 0x74, 0xce, 0x97, 0x37, 0xd8, 0x42, 0xba,
  0x17, 0x00, 0x01, 0x00, 0x29, 0x6c, 0x0f, 0x00, 0x78, 0x01, 0xed, 0x97,
  0x3d, 0x6b, 0x14, 0x51, 0x14, 0x86, 0xdf, 0xfb, 0xb1, 0xb3, 0xdf, 0xb3,
  0x8b, 0x58, 0xc4, 0xe0, 0x0f, 0x10, 0x04, 0x49, 0x23, 0x1a, 0xd4, 0x28,
  0x62, 0xe5, 0x16, 0x5b, 0x6d, 0x61, 0x5c, 0xc2, 0x92, 0x4e, 0x10, 0xb4,
  0xb0, 0xbe, 0x4e, 0xa2, 0x90, 0x14, 0x82, 0x31, 0x0a, 0xfa, 0x1f, 0x14,
  0xb1, 0xb1, 0x09, 0x61, 0x36, 0x7e, 0x14, 0xcb, 0x16, 0x16, 0xa9, 0xfc,
  0x09, 0x82, 0x20, 0x41, 0x2c, 0x2c, 0x24, 0xe3, 0x79, 0xe7, 0x23, 0x4e,
  0x64, 0xd1, 0x26, 0x82, 0xe2, 0x3c, 0x70, 0xce, 0xb9, 0xef, 0x70, 0xcf,
  0x9d, 0xcb, 0x9c, 0xbb, 0xec, 0xb9, 0xd7, 0x5b, 0x88, 0x99, 0x7e, 0x5a,
  0xbe, 0xc6, 0xf8, 0xe6, 0xfe, 0xcb, 0xab, 0xfd, 0x0a, 0x50, 0x92, 0xb1,
  0x12, 0x63, 0x24, 0x4f, 0x9a, 0xf4, 0xc0, 0x17, 0x9f, 0x1e, 0xa8, 0xd1,
  0xa5, 0x94, 0xc5, 0xa6, 0xc4, 0xc8, 0x05, 0xba, 0x14, 0xe6, 0x03, 0xc1,
  0x9c, 0xd8, 0x79, 0x8e, 0x7e, 0xe6, 0x90, 0xd8, 0x11, 0xb1, 0xb6, 0x18,
  0xa9, 0xd2, 0xa5, 0x68, 0xb1, 0x24, 0xff, 0x47, 0x24, 0xf9, 0x71, 0x46,
  0x36, 0x97, 0x31, 0xc3, 0xd2, 0x09, 0x2b, 0xed, 0x8f, 0x67, 0x25, 0x5c,
  0x12, 0xc3, 0x26, 0x3e, 0x9d, 0x63, 0x9c, 0x6d, 0x6e, 0x9e, 0x61, 0xbc,
  0x7c, 0xe3, 0xca, 0xc4, 0x7d, 0xfd, 0x2b, 0x4c, 0xfa, 0x16, 0x59, 0x9d,
  0xc8, 0x57, 0xba, 0xdf, 0x90, 0xd5, 0x77, 0x2d, 0xad, 0x6b, 0x56, 0xcb,
  0x2d, 0xb1, 0x49, 0xeb, 0x93, 0x48, 0x60, 0x9c, 0x04, 0x73, 0x3c, 0x65,
  0x02, 0xc8, 0x19, 0xfa, 0x5f, 0x69, 0xd0, 0x09, 0xfc, 0x16, 0x3c, 0x93,
  0x3c, 0xdf, 0xe9, 0xcf, 0x2c, 0x26, 0x3b, 0x9b, 0xb3, 0x74, 0x08, 0x86,
  0xb4, 0xb5, 0xa9, 0xac, 0x5c, 0x89, 0x56, 0xa2, 0x93, 0x79, 0x89, 0x36,
  0xd4, 0x71, 0xb1, 0x72, 0xda, 0xc8, 0x5a, 0x75, 0x2c, 0xe8, 0xb2, 0x5e,
  0x68, 0x1d, 0x95, 0x7c, 0x79, 0xa1, 0xe8, 0xbe, 0xe8, 0x7e, 0x4e, 0xcf,
  0x8b, 0x9e, 0xcf, 0xe9, 0x81, 0xe8, 0x41, 0x4e, 0x2f, 0x8a, 0x5e, 0xcc,
  0x74, 0xb6, 0x7e, 0x2b, 0x7e, 0x9f, 0x36, 0xbf, 0xaa, 0xf5, 0xdf, 0x42,
  0xb1, 0xc7, 0x83, 0xa1, 0xd8, 0xe3, 0xc1, 0x50, 0xec, 0xb1, 0xa0, 0xa0,
  0xa0, 0xa0, 0xe0, 0x4f, 0xe3, 0xec, 0xa3, 0xd0, 0xd5, 0x76, 0x43, 0x63,
  0x96, 0xc3, 0xc0, 0xdc, 0x09, 0x61, 0xde, 0x6e, 0x79, 0xe6, 0x5b, 0x08,
  0x54, 0x46, 0x50, 0x8d, 0x51, 0x29, 0x52, 0xab, 0xec, 0x40, 0xad, 0x09,
  0xc2, 0x57, 0x32, 0x27, 0x92, 0x39, 0xcf, 0xba, 0x1a, 0xeb, 0x33, 0xed,
  0x17, 0x91, 0x79, 0x10, 0x62, 0x27, 0xc2, 0xf3, 0xfa, 0x7a, 0xb8, 0x54,
  0x7f, 0x18, 0x2a, 0x54, 0x47, 0x4a, 0x35, 0x47, 0xee, 0xf0, 0xee, 0xca,
  0x6d, 0xdc, 0x1b, 0xa2, 0x15, 0xec, 0x68, 0x2c, 0xb3, 0x91, 0x7d, 0x7d,
  0x53, 0x74, 0x09, 0xc1, 0x36, 0x30, 0x36, 0x1e, 0xa3, 0x1d, 0x1b, 0xe8,
  0x8a, 0xaf, 0x38, 0xd6, 0x63, 0xa3, 0x7a, 0xda, 0x95, 0x7a, 0x35, 0xe7,
  0xf5, 0x1a, 0x0e, 0xd6, 0xf2, 0x36, 0xe1, 0xc3, 0xf8, 0xdb, 0xa8, 0x6b,
  0x28, 0x89, 0xd6, 0x68, 0x68, 0x89, 0xba, 0x29, 0x1d, 0x71, 0x17, 0x4e,
  0x75, 0xb5, 0xd3, 0x5d, 0xeb, 0xe4, 0x4f, 0xc8, 0x3f, 0xb1, 0xf1, 0x61,
  0x2e, 0xd2, 0x3a, 0x89, 0x92, 0xcb, 0x88, 0x4e, 0xc5, 0xa9, 0x4e, 0xcd,
  0xe9, 0x8e, 0x75, 0xd2, 0xa3, 0xee, 0xeb, 0x71, 0x81, 0xa5, 0xe1, 0x34,
  0x83, 0x92, 0x06, 0x18, 0x98, 0xa1, 0x23, 0x7c, 0xa6, 0xb4, 0x65, 0xbf,
  0xbd, 0x77, 0x0d, 0x8d, 0xa7, 0x27, 0x8d, 0xf4, 0x80, 0x6e, 0x8f, 0xca,
  0xfe, 0x5c, 0xf6, 0xe9, 0xca, 0xc6, 0x13, 0xf3, 0x57, 0xd8, 0x98, 0x46,
  0xda, 0xbc, 0x9f, 0x16, 0xe3, 0x1d, 0x55, 0x21, 0xce, 0x8d, 0x97, 0xf5,
  0xe4, 0x06, 0xc5, 0xfe, 0x5e, 0xc5, 0x2b, 0x24, 0x58, 0x79, 0x4a, 0xaa,
  0x77, 0xdb, 0x27, 0x51, 0xff, 0x7c, 0xec, 0xf8, 0xad, 0x77, 0x8f, 0x4f,
  0xbd, 0xbf, 0xb8, 0xf1, 0x1d, 0xcf, 0xce, 0x9d, 0x04, 0x00, 0x00, 0x00,
  0x02, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x04, 0x01, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x92, 0x30, 0x00, 0x00,
  0x00, 0xf0, 0xff, 0x00, 0x00, 0x00, 0x00, 0x74, 0x00, 0x00, 0x00, 0x80,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x03, 0x00, 0x08, 0x02, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x01, 0x02, 0x04, 0x02, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x88, 0x00, 0x00, 0x78, 0x01, 0x4d, 0xcc, 0xbb, 0x0d, 0x80, 0x30,
  0x0c, 0x06, 0xe1, 0x9f, 0x47, 0x7a, 0xca, 0x54, 0xcc, 0x40, 0xc9, 0x10,
  0x94, 0xec, 0x93, 0xd1, 0xcd, 0x5d, 0x11, 0x89, 0x93, 0x3e, 0xd9, 0x92,
  0xa3, 0x2c, 0x49, 0x56, 0x74, 0xb8, 0xbf, 0x38, 0x61, 0x0d, 0x17, 0xbc,
  0xbb, 0x3f, 0xf0, 0xcd, 0x0d, 0x73, 0x9f, 0x15, 0x39, 0x67, 0xdb, 0x8f,
  0x1d, 0xd8, 0xe1, 0x5f, 0x56, 0x35, 0x86, 0xd3, 0x5a, 0x92, 0x0f, 0xb3,
  0xbf, 0x08, 0x6d, 0x00, 0x78, 0x62, 0x6f, 0x70, 0x01, 0x00, 0x00, 0x00,
  0x7e, 0x02, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00
};
