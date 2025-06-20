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
; shader debug name: C:\Users\marcu\Downloads\DirectXTK12-main\DirectXTK12-main\Src/Shaders/Compiled\XboxGamingXboxOneToneMap_PS_SRGB.pdb
; shader hash: b70bffeaf511e5ebfc16f8e8e632e023
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
; EntryFunctionName: PS_SRGB
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
;   output 0 depends on inputs: { 4, 5 }
;   output 1 depends on inputs: { 4, 5 }
;   output 2 depends on inputs: { 4, 5 }
;   output 3 depends on inputs: { 4, 5 }
;
target datalayout = "e-m:e-p:32:32-i1:32-i8:32-i16:32-i32:32-i64:64-f16:32-f32:32-f64:64-n8:16:32:64"
target triple = "dxil-ms-xb1"

%dx.types.Handle = type { i8* }
%dx.types.ResRet.f32 = type { float, float, float, float, i32 }
%"class.Texture2D<vector<float, 4> >" = type { <4 x float>, %"class.Texture2D<vector<float, 4> >::mips_type" }
%"class.Texture2D<vector<float, 4> >::mips_type" = type { i32 }
%struct.SamplerState = type { i32 }

define void @PS_SRGB() {
  %1 = call %dx.types.Handle @dx.op.createHandle(i32 57, i8 0, i32 0, i32 0, i1 false)  ; CreateHandle(resourceClass,rangeId,index,nonUniformIndex)
  %2 = call %dx.types.Handle @dx.op.createHandle(i32 57, i8 3, i32 0, i32 0, i1 false)  ; CreateHandle(resourceClass,rangeId,index,nonUniformIndex)
  %3 = call float @dx.op.loadInput.f32(i32 4, i32 1, i32 0, i8 0, i32 undef)  ; LoadInput(inputSigId,rowIndex,colIndex,gsVertexAxis)
  %4 = call float @dx.op.loadInput.f32(i32 4, i32 1, i32 0, i8 1, i32 undef)  ; LoadInput(inputSigId,rowIndex,colIndex,gsVertexAxis)
  %5 = call %dx.types.ResRet.f32 @dx.op.sample.f32(i32 60, %dx.types.Handle %1, %dx.types.Handle %2, float %3, float %4, float undef, float undef, i32 0, i32 0, i32 undef, float undef)  ; Sample(srv,sampler,coord0,coord1,coord2,coord3,offset0,offset1,offset2,clamp)
  %6 = extractvalue %dx.types.ResRet.f32 %5, 0
  %7 = extractvalue %dx.types.ResRet.f32 %5, 1
  %8 = extractvalue %dx.types.ResRet.f32 %5, 2
  %9 = extractvalue %dx.types.ResRet.f32 %5, 3
  %10 = call float @dx.op.unary.f32(i32 6, float %6)  ; FAbs(value)
  %11 = call float @dx.op.unary.f32(i32 6, float %7)  ; FAbs(value)
  %12 = call float @dx.op.unary.f32(i32 6, float %8)  ; FAbs(value)
  %13 = call float @dx.op.unary.f32(i32 23, float %10)  ; Log(value)
  %14 = call float @dx.op.unary.f32(i32 23, float %11)  ; Log(value)
  %15 = call float @dx.op.unary.f32(i32 23, float %12)  ; Log(value)
  %16 = fmul fast float %13, 0x3FDD1745C0000000
  %17 = fmul fast float %14, 0x3FDD1745C0000000
  %18 = fmul fast float %15, 0x3FDD1745C0000000
  %19 = call float @dx.op.unary.f32(i32 21, float %16)  ; Exp(value)
  %20 = call float @dx.op.unary.f32(i32 21, float %17)  ; Exp(value)
  %21 = call float @dx.op.unary.f32(i32 21, float %18)  ; Exp(value)
  call void @dx.op.storeOutput.f32(i32 5, i32 0, i32 0, i8 0, float %19)  ; StoreOutput(outputSigId,rowIndex,colIndex,value)
  call void @dx.op.storeOutput.f32(i32 5, i32 0, i32 0, i8 1, float %20)  ; StoreOutput(outputSigId,rowIndex,colIndex,value)
  call void @dx.op.storeOutput.f32(i32 5, i32 0, i32 0, i8 2, float %21)  ; StoreOutput(outputSigId,rowIndex,colIndex,value)
  call void @dx.op.storeOutput.f32(i32 5, i32 0, i32 0, i8 3, float %9)  ; StoreOutput(outputSigId,rowIndex,colIndex,value)
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
!11 = !{[8 x i32] [i32 6, i32 4, i32 0, i32 0, i32 0, i32 0, i32 15, i32 15]}
!12 = !{void ()* @PS_SRGB, !"PS_SRGB", !13, !5, null}
!13 = !{!14, !19, null}
!14 = !{!15, !17}
!15 = !{i32 0, !"SV_Position", i8 9, i8 3, !16, i8 4, i32 1, i8 4, i32 0, i8 0, null}
!16 = !{i32 0}
!17 = !{i32 1, !"TEXCOORD", i8 9, i8 0, !16, i8 2, i32 1, i8 2, i32 1, i8 0, !18}
!18 = !{i32 3, i32 3}
!19 = !{!20}
!20 = !{i32 0, !"SV_Target", i8 9, i8 16, !16, i8 0, i32 1, i8 4, i32 0, i8 0, !21}
!21 = !{i32 3, i32 15}

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
  s_mov_b64     s[4:5], exec
  s_wqm_b64     exec, exec // wrscc
  s_mov_b32     s2, s3
  s_mov_b32     s3, 0
  s_load_dwordx8  s[8:15], s[2:3], 0x00
  s_mov_b32     m0, s6
  v_interp_p1_f32  v2, v0, attr0.x
  v_interp_p1_f32  v3, v0, attr0.y
  v_interp_p2_f32  v2, v1, attr0.x
  v_interp_p2_f32  v3, v1, attr0.y
  s_movk_i32    s0, 0x3092
  s_mov_b32     s1, 0x00fff000
  s_brev_b32    s2, 46
  s_brev_b32    s3, 1
  s_and_b64     exec, exec, s[4:5] // wrscc
  s_waitcnt     lgkmcnt(0)
  image_sample  v[0:3], v[2:3], s[8:15], s[0:3] dmask:0xf
  s_waitcnt     vmcnt(0)
  v_log_f32     v1, abs(v1)
  v_log_f32     v2, abs(v2)
  v_log_f32     v0, abs(v0)
  v_mul_legacy_f32  v1, 0x3ee8ba2e, v1
  v_mul_legacy_f32  v2, 0x3ee8ba2e, v2
  v_mul_legacy_f32  v0, 0x3ee8ba2e, v0
  v_exp_f32     v4, v1
  v_exp_f32     v2, v2
  v_exp_f32     v5, v0
  v_cvt_pkrtz_f16_f32  v0, v5, v4
  v_cvt_pkrtz_f16_f32  v1, v2, v3
  exp           mrt0, v0, v0, v1, v1 done compr vm
  s_endpgm      
end


NumVGPR=6,NumSGPR=18,LDS=0,Scratch=0,Occpancy=10


#endif

const unsigned char ToneMap_PS_SRGB[] = {
  0x44, 0x58, 0x42, 0x43, 0xea, 0x0b, 0xea, 0x44, 0xeb, 0x29, 0x92, 0x3e,
  0x95, 0xf9, 0xb3, 0x51, 0xa7, 0x1b, 0xf1, 0x52, 0x01, 0x00, 0x00, 0x00,
  0x1c, 0x0e, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00,
  0x50, 0x00, 0x00, 0x00, 0xb8, 0x00, 0x00, 0x00, 0xf4, 0x00, 0x00, 0x00,
  0xe0, 0x01, 0x00, 0x00, 0x70, 0x02, 0x00, 0x00, 0xf4, 0x02, 0x00, 0x00,
  0x10, 0x03, 0x00, 0x00, 0x53, 0x46, 0x49, 0x30, 0x08, 0x00, 0x00, 0x00,
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
  0x74, 0x00, 0x00, 0x00, 0x50, 0x53, 0x56, 0x30, 0xe4, 0x00, 0x00, 0x00,
  0x34, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x02, 0x01, 0x00, 0x02,
  0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x0a, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
  0x18, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x00, 0x54, 0x45, 0x58,
  0x43, 0x4f, 0x4f, 0x52, 0x44, 0x00, 0x50, 0x53, 0x5f, 0x53, 0x52, 0x47,
  0x42, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x01, 0x00, 0x44, 0x03, 0x03, 0x04, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x42, 0x00, 0x03, 0x02, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x44, 0x10,
  0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00,
  0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x52, 0x54, 0x53, 0x30, 0x88, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x02, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x54, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x05, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
  0x05, 0x00, 0x00, 0x00, 0x4c, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
  0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x7f, 0x7f,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00,
  0x49, 0x4c, 0x44, 0x4e, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x74, 0x00,
  0x43, 0x3a, 0x5c, 0x55, 0x73, 0x65, 0x72, 0x73, 0x5c, 0x6d, 0x61, 0x72,
  0x63, 0x75, 0x5c, 0x44, 0x6f, 0x77, 0x6e, 0x6c, 0x6f, 0x61, 0x64, 0x73,
  0x5c, 0x44, 0x69, 0x72, 0x65, 0x63, 0x74, 0x58, 0x54, 0x4b, 0x31, 0x32,
  0x2d, 0x6d, 0x61, 0x69, 0x6e, 0x5c, 0x44, 0x69, 0x72, 0x65, 0x63, 0x74,
  0x58, 0x54, 0x4b, 0x31, 0x32, 0x2d, 0x6d, 0x61, 0x69, 0x6e, 0x5c, 0x53,
  0x72, 0x63, 0x2f, 0x53, 0x68, 0x61, 0x64, 0x65, 0x72, 0x73, 0x2f, 0x43,
  0x6f, 0x6d, 0x70, 0x69, 0x6c, 0x65, 0x64, 0x5c, 0x58, 0x62, 0x6f, 0x78,
  0x47, 0x61, 0x6d, 0x69, 0x6e, 0x67, 0x58, 0x62, 0x6f, 0x78, 0x4f, 0x6e,
  0x65, 0x54, 0x6f, 0x6e, 0x65, 0x4d, 0x61, 0x70, 0x5f, 0x50, 0x53, 0x5f,
  0x53, 0x52, 0x47, 0x42, 0x2e, 0x70, 0x64, 0x62, 0x00, 0x00, 0x00, 0x00,
  0x48, 0x41, 0x53, 0x48, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xb7, 0x0b, 0xff, 0xea, 0xf5, 0x11, 0xe5, 0xeb, 0xfc, 0x16, 0xf8, 0xe8,
  0xe6, 0x32, 0xe0, 0x23, 0x44, 0x58, 0x49, 0x4c, 0x04, 0x0b, 0x00, 0x00,
  0x60, 0x00, 0x00, 0x00, 0xc1, 0x02, 0x00, 0x00, 0x44, 0x58, 0x49, 0x4c,
  0x00, 0x01, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x00, 0x64, 0x07, 0x00, 0x00,
  0x58, 0x44, 0x41, 0x54, 0x06, 0x00, 0x00, 0x00, 0x24, 0x00, 0x00, 0x00,
  0x07, 0x00, 0x00, 0x00, 0x6c, 0x00, 0x00, 0x00, 0x7c, 0x07, 0x00, 0x00,
  0x10, 0x00, 0x00, 0x00, 0xe8, 0x07, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0xf8, 0x07, 0x00, 0x00, 0xf7, 0x01, 0x00, 0x00,
  0x03, 0x00, 0x00, 0x00, 0xf0, 0x09, 0x00, 0x00, 0xb0, 0x00, 0x00, 0x00,
  0x06, 0x00, 0x00, 0x00, 0xa0, 0x0a, 0x00, 0x00, 0x4f, 0x00, 0x00, 0x00,
  0x08, 0x00, 0x00, 0x00, 0xf0, 0x0a, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00,
  0x60, 0x00, 0x00, 0x00, 0xdf, 0x01, 0x00, 0x00, 0x44, 0x58, 0x49, 0x4c,
  0x00, 0x01, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x64, 0x07, 0x00, 0x00,
  0x42, 0x43, 0xc0, 0xde, 0x21, 0x0c, 0x00, 0x00, 0xd6, 0x01, 0x00, 0x00,
  0x0b, 0x82, 0x20, 0x00, 0x02, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00,
  0x07, 0x81, 0x23, 0x91, 0x41, 0xc8, 0x04, 0x49, 0x06, 0x10, 0x32, 0x39,
  0x92, 0x01, 0x84, 0x0c, 0x25, 0x05, 0x08, 0x19, 0x1e, 0x04, 0x8b, 0x62,
  0x80, 0x14, 0x45, 0x02, 0x42, 0x92, 0x0b, 0x42, 0xa4, 0x10, 0x32, 0x14,
  0x38, 0x08, 0x18, 0x4b, 0x0a, 0x32, 0x52, 0x88, 0x48, 0x90, 0x14, 0x20,
  0x43, 0x46, 0x88, 0xa5, 0x00, 0x19, 0x32, 0x42, 0xe4, 0x48, 0x0e, 0x90,
  0x91, 0x22, 0xc4, 0x50, 0x41, 0x51, 0x81, 0x8c, 0xe1, 0x83, 0xe5, 0x8a,
  0x04, 0x29, 0x46, 0x06, 0x51, 0x18, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00,
  0x1b, 0x8c, 0xe0, 0xff, 0xff, 0xff, 0xff, 0x07, 0x40, 0x02, 0xa8, 0x0d,
  0x84, 0xf0, 0xff, 0xff, 0xff, 0xff, 0x03, 0x20, 0x6d, 0x30, 0x86, 0xff,
  0xff, 0xff, 0xff, 0x1f, 0x00, 0x09, 0xa8, 0x00, 0x49, 0x18, 0x00, 0x00,
  0x03, 0x00, 0x00, 0x00, 0x13, 0x82, 0x60, 0x42, 0x20, 0x4c, 0x08, 0x06,
  0x00, 0x00, 0x00, 0x00, 0x89, 0x20, 0x00, 0x00, 0x44, 0x00, 0x00, 0x00,
  0x32, 0x22, 0x48, 0x09, 0x20, 0x64, 0x85, 0x04, 0x93, 0x22, 0xa4, 0x84,
  0x04, 0x93, 0x22, 0xe3, 0x84, 0xa1, 0x90, 0x14, 0x12, 0x4c, 0x8a, 0x8c,
  0x0b, 0x84, 0xa4, 0x4c, 0x10, 0x70, 0x23, 0x00, 0x25, 0x00, 0x14, 0x66,
  0x00, 0xe6, 0x08, 0xc0, 0x60, 0x8e, 0x00, 0x29, 0xc6, 0x20, 0x84, 0x14,
  0x42, 0xa6, 0x18, 0x80, 0x10, 0x52, 0x06, 0xa1, 0x9b, 0x86, 0xcb, 0x9f,
  0xb0, 0x87, 0x90, 0xfc, 0x95, 0x90, 0x56, 0x62, 0xf2, 0x8b, 0xdb, 0x46,
  0xc5, 0x18, 0x63, 0x10, 0x2a, 0xf7, 0x0c, 0x97, 0x3f, 0x61, 0x0f, 0x21,
  0xf9, 0x21, 0xd0, 0x0c, 0x0b, 0x81, 0x82, 0x55, 0x18, 0x45, 0x18, 0x1b,
  0x63, 0x0c, 0x42, 0xc8, 0xa0, 0x56, 0x86, 0x41, 0x06, 0xbd, 0x39, 0x82,
  0xa0, 0x18, 0x8c, 0x14, 0x42, 0x22, 0xc9, 0x81, 0x80, 0x61, 0x04, 0x62,
  0x98, 0xa9, 0x0d, 0xc6, 0x81, 0x1d, 0xc2, 0x61, 0x1e, 0xe6, 0xc1, 0x0d,
  0x68, 0xa1, 0x1c, 0xf0, 0x81, 0x1e, 0xea, 0x41, 0x1e, 0xca, 0x41, 0x0e,
  0x48, 0x81, 0x0f, 0xec, 0xa1, 0x1c, 0xc6, 0x81, 0x1e, 0xde, 0x41, 0x1e,
  0xf8, 0xc0, 0x1c, 0xd8, 0xe1, 0x1d, 0xc2, 0x81, 0x1e, 0xd8, 0x00, 0x0c,
  0xe8, 0xc0, 0x0f, 0xc0, 0xc0, 0x0f, 0xf4, 0x40, 0x0f, 0xda, 0x21, 0x1d,
  0xe0, 0x61, 0x1e, 0x7e, 0x81, 0x1e, 0xf2, 0x01, 0x1e, 0xca, 0x01, 0x05,
  0x64, 0x26, 0x31, 0x18, 0x07, 0x76, 0x08, 0x87, 0x79, 0x98, 0x07, 0x37,
  0xa0, 0x85, 0x72, 0xc0, 0x07, 0x7a, 0xa8, 0x07, 0x79, 0x28, 0x07, 0x39,
  0x20, 0x05, 0x3e, 0xb0, 0x87, 0x72, 0x18, 0x07, 0x7a, 0x78, 0x07, 0x79,
  0xe0, 0x03, 0x73, 0x60, 0x87, 0x77, 0x08, 0x07, 0x7a, 0x60, 0x03, 0x30,
  0xa0, 0x03, 0x3f, 0x00, 0x03, 0x3f, 0x40, 0x42, 0xb5, 0x74, 0x6f, 0x92,
  0xa6, 0x88, 0x12, 0x26, 0x9f, 0x05, 0x98, 0x67, 0x21, 0x22, 0x76, 0x02,
  0x26, 0x02, 0x05, 0x84, 0x72, 0x22, 0x10, 0x00, 0x13, 0x16, 0x72, 0xc0,
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
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x43, 0x9e, 0x07, 0x08,
  0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x86, 0x3c, 0x12,
  0x10, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x64, 0x81,
  0x00, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x32, 0x1e, 0x98, 0x14,
  0x19, 0x11, 0x4c, 0x90, 0x8c, 0x09, 0x26, 0x47, 0xc6, 0x04, 0x43, 0x22,
  0x25, 0x30, 0x02, 0x50, 0x10, 0xc5, 0x50, 0x04, 0x25, 0x51, 0x06, 0xe5,
  0x41, 0xa5, 0x24, 0xca, 0xa0, 0x10, 0x46, 0x00, 0x8a, 0xa0, 0x40, 0x08,
  0xcf, 0x00, 0x90, 0x9e, 0x01, 0xa0, 0x3d, 0x16, 0x62, 0x10, 0x00, 0x00,
  0x00, 0xcf, 0x03, 0x00, 0x79, 0x18, 0x00, 0x00, 0x72, 0x00, 0x00, 0x00,
  0x1a, 0x03, 0x4c, 0x90, 0x46, 0x02, 0x13, 0xc4, 0x36, 0xf8, 0xfa, 0xc2,
  0x12, 0x7a, 0xc2, 0xfa, 0x82, 0x2a, 0x92, 0xfa, 0xa2, 0x42, 0x92, 0x2a,
  0x0a, 0x22, 0xfa, 0x9a, 0x1a, 0x92, 0x0a, 0xa2, 0x1a, 0x42, 0xfa, 0x9a,
  0x4a, 0xd2, 0x2a, 0xfa, 0x62, 0x4a, 0x6a, 0x4a, 0xa2, 0xfa, 0x4a, 0x72,
  0xfa, 0x12, 0xca, 0xa2, 0x2a, 0x9a, 0x62, 0x00, 0xb3, 0x41, 0x08, 0x04,
  0x76, 0x64, 0x78, 0x63, 0x78, 0x62, 0x6f, 0x78, 0x20, 0x32, 0x34, 0x31,
  0x30, 0x2e, 0x32, 0x34, 0x31, 0x30, 0x2e, 0x31, 0x31, 0x31, 0x31, 0x36,
  0x2e, 0x31, 0x30, 0x37, 0x34, 0x31, 0x1b, 0x02, 0x62, 0x82, 0x40, 0x18,
  0x13, 0x04, 0xe2, 0xd8, 0x20, 0x18, 0xc7, 0x04, 0x81, 0x40, 0x36, 0x08,
  0x46, 0x42, 0x01, 0x6e, 0x6e, 0x82, 0x40, 0x24, 0x1b, 0x86, 0x85, 0x39,
  0x26, 0x08, 0x18, 0x45, 0x60, 0x82, 0x40, 0x28, 0x13, 0x04, 0x62, 0xd9,
  0x20, 0x1c, 0xd1, 0x86, 0xe4, 0x70, 0x9e, 0xe3, 0x30, 0xa0, 0x43, 0xda,
  0x10, 0x4c, 0x13, 0x04, 0xad, 0xda, 0x80, 0x1c, 0xd5, 0x73, 0x1c, 0xc6,
  0x01, 0x6c, 0x08, 0xac, 0x0d, 0x04, 0x05, 0x00, 0xd7, 0x04, 0x61, 0xb3,
  0x36, 0x04, 0xd9, 0x04, 0x41, 0x00, 0x78, 0x40, 0x4d, 0x7d, 0x4d, 0x49,
  0x1d, 0x09, 0x71, 0x99, 0xb2, 0xfa, 0x82, 0x7a, 0x9b, 0x4b, 0xa3, 0x4b,
  0x7b, 0x73, 0x9b, 0x20, 0x14, 0xce, 0x04, 0xa1, 0x78, 0x36, 0x04, 0xc7,
  0x04, 0xa1, 0x80, 0x26, 0x08, 0x45, 0xb4, 0x61, 0x39, 0x3a, 0xef, 0x03,
  0x83, 0x30, 0x30, 0xc2, 0xe0, 0x10, 0x03, 0x80, 0x08, 0x55, 0x11, 0xd6,
  0xd0, 0xd3, 0x93, 0x14, 0xd1, 0x04, 0xa1, 0x90, 0x26, 0x08, 0x04, 0xb3,
  0x41, 0x30, 0x03, 0x33, 0xd8, 0xb0, 0x18, 0x64, 0xe0, 0x89, 0x01, 0x18,
  0x94, 0x81, 0x51, 0x06, 0x86, 0x18, 0x9c, 0xc1, 0x06, 0x61, 0x0c, 0xd0,
  0x80, 0xc9, 0x94, 0xd5, 0x17, 0x55, 0x98, 0xdc, 0x59, 0x19, 0xdd, 0x04,
  0xa1, 0x98, 0x26, 0x08, 0x44, 0xb3, 0x41, 0x30, 0x03, 0x36, 0xd8, 0xb0,
  0x1c, 0x6a, 0xe0, 0xad, 0x01, 0x18, 0x88, 0x81, 0x11, 0x06, 0x87, 0x18,
  0xb4, 0xc1, 0x86, 0xc0, 0x0d, 0x36, 0x0c, 0x69, 0xf0, 0x06, 0xc0, 0x86,
  0x62, 0xe3, 0xe0, 0x00, 0x03, 0x5a, 0xe1, 0x89, 0xbd, 0xe1, 0xb9, 0x8c,
  0xbd, 0xb5, 0xc1, 0xa5, 0xb1, 0x95, 0xc9, 0xb9, 0xbc, 0xc1, 0xd1, 0xa5,
  0xbd, 0xb9, 0xcd, 0x4d, 0x09, 0x84, 0x2a, 0x6c, 0x6c, 0x76, 0x6d, 0x2e,
  0x69, 0x64, 0x65, 0x6e, 0x74, 0x53, 0x02, 0xa2, 0x0a, 0x19, 0x9e, 0x8b,
  0x5d, 0x99, 0xdc, 0x5c, 0xda, 0x9b, 0xdb, 0x94, 0xe0, 0x68, 0x42, 0x86,
  0xe7, 0x62, 0x17, 0xc6, 0x66, 0x57, 0x26, 0x37, 0x25, 0x48, 0xea, 0x90,
  0xe1, 0xb9, 0xcc, 0xa1, 0x85, 0x91, 0x95, 0xc9, 0x35, 0xbd, 0x91, 0x95,
  0xb1, 0x4d, 0x09, 0x98, 0x32, 0x64, 0x78, 0x2e, 0x72, 0x65, 0x73, 0x6f,
  0x75, 0x72, 0x63, 0x65, 0x73, 0x53, 0x82, 0xab, 0x0e, 0x19, 0x9e, 0x8b,
  0x5d, 0x5a, 0xd9, 0x5d, 0x12, 0xd9, 0x14, 0x5d, 0x18, 0x5d, 0xd9, 0x94,
  0x20, 0xab, 0x43, 0x86, 0xe7, 0x52, 0xe6, 0x46, 0x27, 0x97, 0x07, 0xf5,
  0x96, 0xe6, 0x46, 0x37, 0x37, 0x25, 0x80, 0x03, 0x00, 0x00, 0x00, 0x00,
  0x79, 0x18, 0x00, 0x00, 0x4c, 0x00, 0x00, 0x00, 0x33, 0x08, 0x80, 0x1c,
  0xc4, 0xe1, 0x1c, 0x66, 0x14, 0x01, 0x3d, 0x88, 0x43, 0x38, 0x84, 0xc3,
  0x8c, 0x42, 0x80, 0x07, 0x79, 0x78, 0x07, 0x73, 0x98, 0x71, 0x0c, 0xe6,
  0x00, 0x0f, 0xed, 0x10, 0x0e, 0xf4, 0x80, 0x0e, 0x33, 0x0c, 0x42, 0x1e,
  0xc2, 0xc1, 0x1d, 0xce, 0xa1, 0x1c, 0x66, 0x30, 0x05, 0x3d, 0x88, 0x43,
  0x38, 0x84, 0x83, 0x1b, 0xcc, 0x03, 0x3d, 0xc8, 0x43, 0x3d, 0x8c, 0x03,
  0x3d, 0xcc, 0x78, 0x8c, 0x74, 0x70, 0x07, 0x7b, 0x08, 0x07, 0x79, 0x48,
  0x87, 0x70, 0x70, 0x07, 0x7a, 0x70, 0x03, 0x76, 0x78, 0x87, 0x70, 0x20,
  0x87, 0x19, 0xcc, 0x11, 0x0e, 0xec, 0x90, 0x0e, 0xe1, 0x30, 0x0f, 0x6e,
  0x30, 0x0f, 0xe3, 0xf0, 0x0e, 0xf0, 0x50, 0x0e, 0x33, 0x10, 0xc4, 0x1d,
  0xde, 0x21, 0x1c, 0xd8, 0x21, 0x1d, 0xc2, 0x61, 0x1e, 0x66, 0x30, 0x89,
  0x3b, 0xbc, 0x83, 0x3b, 0xd0, 0x43, 0x39, 0xb4, 0x03, 0x3c, 0xbc, 0x83,
  0x3c, 0x84, 0x03, 0x3b, 0xcc, 0xf0, 0x14, 0x76, 0x60, 0x07, 0x7b, 0x68,
  0x07, 0x37, 0x68, 0x87, 0x72, 0x68, 0x07, 0x37, 0x80, 0x87, 0x70, 0x90,
  0x87, 0x70, 0x60, 0x07, 0x76, 0x28, 0x07, 0x76, 0xf8, 0x05, 0x76, 0x78,
  0x87, 0x77, 0x80, 0x87, 0x5f, 0x08, 0x87, 0x71, 0x18, 0x87, 0x72, 0x98,
  0x87, 0x79, 0x98, 0x81, 0x2c, 0xee, 0xf0, 0x0e, 0xee, 0xe0, 0x0e, 0xf5,
  0xc0, 0x0e, 0xec, 0x30, 0x03, 0x62, 0xc8, 0xa1, 0x1c, 0xe4, 0xa1, 0x1c,
  0xcc, 0xa1, 0x1c, 0xe4, 0xa1, 0x1c, 0xdc, 0x61, 0x1c, 0xca, 0x21, 0x1c,
  0xc4, 0x81, 0x1d, 0xca, 0x61, 0x06, 0xd6, 0x90, 0x43, 0x39, 0xc8, 0x43,
  0x39, 0x98, 0x43, 0x39, 0xc8, 0x43, 0x39, 0xb8, 0xc3, 0x38, 0x94, 0x43,
  0x38, 0x88, 0x03, 0x3b, 0x94, 0xc3, 0x2f, 0xbc, 0x83, 0x3c, 0xfc, 0x82,
  0x3b, 0xd4, 0x03, 0x3b, 0xb0, 0xc3, 0x0c, 0xc4, 0x21, 0x07, 0x7c, 0x70,
  0x03, 0x7a, 0x28, 0x87, 0x76, 0x80, 0x87, 0x19, 0xd1, 0x43, 0x0e, 0xf8,
  0xe0, 0x06, 0xe4, 0x20, 0x0e, 0xe7, 0xe0, 0x06, 0xf6, 0x10, 0x0e, 0xf2,
  0xc0, 0x0e, 0xe1, 0x90, 0x0f, 0xef, 0x50, 0x0f, 0xf4, 0x00, 0x00, 0x00,
  0x71, 0x20, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x06, 0x70, 0xa4, 0xec,
  0xcf, 0xae, 0xe0, 0x66, 0x05, 0xd2, 0x70, 0xf9, 0xce, 0xe3, 0x0b, 0x11,
  0x01, 0x4c, 0x44, 0x08, 0x34, 0xc3, 0x42, 0x58, 0xc0, 0x34, 0x5c, 0xbe,
  0xf3, 0xf8, 0x8b, 0x03, 0x0c, 0x62, 0xf3, 0x50, 0x93, 0x5f, 0xdc, 0xb6,
  0x0d, 0x40, 0xc3, 0xe5, 0x3b, 0x8f, 0x2f, 0x01, 0xcc, 0xb3, 0x10, 0x7e,
  0x71, 0xdb, 0x26, 0x50, 0x0d, 0x97, 0xef, 0x3c, 0xbe, 0x34, 0x39, 0x11,
  0x81, 0x52, 0xd3, 0x43, 0x4d, 0x7e, 0x71, 0xdb, 0x46, 0xf0, 0x0c, 0x97,
  0xef, 0x3c, 0x3e, 0xd5, 0x00, 0x11, 0xe6, 0x17, 0xb7, 0x0d, 0x00, 0x00,
  0x61, 0x20, 0x00, 0x00, 0x47, 0x00, 0x00, 0x00, 0x13, 0x04, 0x41, 0x2c,
  0x10, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x14, 0x47, 0x00, 0xa8,
  0x94, 0x00, 0x91, 0x52, 0x98, 0x01, 0x28, 0x97, 0x52, 0x29, 0xb9, 0x42,
  0x28, 0x3c, 0x1a, 0x63, 0x04, 0x6e, 0xec, 0xc6, 0xee, 0x37, 0x03, 0x00,
  0x23, 0x06, 0x09, 0x00, 0x82, 0x60, 0x20, 0x75, 0x45, 0xb4, 0x6d, 0xcb,
  0x88, 0x41, 0x02, 0x80, 0x20, 0x18, 0x48, 0x9e, 0x41, 0x71, 0x1c, 0x33,
  0x62, 0x90, 0x00, 0x20, 0x08, 0x06, 0xc6, 0x18, 0x18, 0x5e, 0x37, 0x29,
  0x23, 0x06, 0x09, 0x00, 0x82, 0x60, 0x60, 0x90, 0xc1, 0xf1, 0x79, 0xcd,
  0x32, 0x62, 0xf0, 0x00, 0x20, 0x08, 0x06, 0xcd, 0x18, 0x1c, 0xc4, 0x20,
  0x04, 0x45, 0xf1, 0x7d, 0x4c, 0x31, 0x9a, 0x10, 0x00, 0xa3, 0x09, 0x42,
  0x30, 0x9a, 0x30, 0x08, 0xa3, 0x09, 0xc4, 0x30, 0x62, 0x60, 0x00, 0x20,
  0x08, 0x06, 0xcf, 0x19, 0x88, 0x01, 0x31, 0x62, 0x60, 0x00, 0x20, 0x08,
  0x06, 0x0f, 0x1a, 0x8c, 0x01, 0x31, 0x62, 0x60, 0x00, 0x20, 0x08, 0x06,
  0x4f, 0x1a, 0x90, 0x01, 0x31, 0x62, 0x60, 0x00, 0x20, 0x08, 0x06, 0x8f,
  0x1a, 0x4c, 0xc3, 0x88, 0x81, 0x01, 0x80, 0x20, 0x18, 0x3c, 0x6b, 0x40,
  0x0d, 0x23, 0x06, 0x06, 0x00, 0x82, 0x60, 0xf0, 0xb0, 0x41, 0x35, 0xd8,
  0x10, 0xc9, 0xc7, 0x06, 0x49, 0x3e, 0x36, 0x4c, 0xf2, 0x19, 0x31, 0x30,
  0x00, 0x10, 0x04, 0x83, 0x07, 0x0e, 0xb0, 0x61, 0xc4, 0xc0, 0x00, 0x40,
  0x10, 0x0c, 0x9e, 0x38, 0xc8, 0x86, 0x11, 0x03, 0x03, 0x00, 0x41, 0x30,
  0x78, 0xe4, 0x40, 0x1b, 0x46, 0x0c, 0x12, 0x00, 0x04, 0xc1, 0x00, 0xa9,
  0x03, 0x0f, 0x0e, 0xe0, 0xc0, 0x0c, 0x86, 0x11, 0x83, 0x04, 0x00, 0x41,
  0x30, 0x40, 0xea, 0xc0, 0x83, 0x03, 0x38, 0xf8, 0x84, 0x11, 0x83, 0x04,
  0x00, 0x41, 0x30, 0x40, 0xea, 0xc0, 0x83, 0x03, 0x38, 0x28, 0x83, 0x60,
  0xc4, 0x20, 0x01, 0x40, 0x10, 0x0c, 0x90, 0x3a, 0xf0, 0xe0, 0x00, 0x0e,
  0xd0, 0xa0, 0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0xb7, 0x0b, 0xff, 0xea,
  0xf5, 0x11, 0xe5, 0xeb, 0xfc, 0x16, 0xf8, 0xe8, 0xe6, 0x32, 0xe0, 0x23,
  0x17, 0x00, 0x01, 0x00, 0x29, 0xf4, 0x0e, 0x00, 0x78, 0x01, 0xed, 0x97,
  0xbf, 0x4b, 0x1c, 0x41, 0x14, 0xc7, 0xdf, 0xcc, 0xec, 0x9d, 0xf7, 0xd3,
  0x8d, 0x16, 0x21, 0x88, 0x9d, 0x4d, 0x0a, 0x09, 0x92, 0xca, 0x22, 0x9c,
  0x42, 0x62, 0x75, 0xe0, 0x1f, 0x20, 0x22, 0x87, 0x7f, 0x81, 0xad, 0x20,
  0xeb, 0x9e, 0x0a, 0x49, 0x71, 0x85, 0x58, 0xa5, 0xf4, 0x2f, 0x90, 0x74,
  0x82, 0xc8, 0xde, 0x09, 0x29, 0x16, 0x52, 0xa6, 0xb5, 0xb0, 0x49, 0x90,
  0x84, 0x80, 0x45, 0x02, 0x12, 0xc4, 0xf5, 0xfb, 0xdd, 0xdd, 0xd1, 0x55,
  0x8e, 0xd8, 0x9c, 0xa0, 0x64, 0x3f, 0xf0, 0xde, 0x9b, 0xef, 0xdc, 0xbc,
  0x99, 0xb9, 0x9d, 0x5d, 0x78, 0xf3, 0x7b, 0x58, 0x62, 0x0e, 0x1b, 0x7b,
  0x15, 0xc6, 0xe9, 0xb9, 0xa3, 0x2f, 0x6b, 0x43, 0x22, 0x05, 0xb4, 0x15,
  0x8c, 0x91, 0x7c, 0xac, 0xd3, 0x8b, 0x7c, 0x48, 0xc7, 0xc7, 0x83, 0x53,
  0x8a, 0xb0, 0x51, 0x18, 0x99, 0xa5, 0x4b, 0x61, 0xbe, 0x88, 0xdf, 0x80,
  0xcd, 0xb0, 0x75, 0x17, 0x4e, 0xc5, 0x69, 0xb1, 0x5c, 0x0c, 0xe7, 0xb1,
  0x30, 0x37, 0xc9, 0xbf, 0x89, 0x24, 0xdb, 0xb6, 0x68, 0x18, 0xfb, 0xb3,
  0xbf, 0x39, 0x74, 0x20, 0x7c, 0xfb, 0xf7, 0x0d, 0xc2, 0x3b, 0x98, 0xf4,
  0x7e, 0xbd, 0xc4, 0x5e, 0x44, 0xd6, 0x56, 0x0b, 0xec, 0x93, 0xce, 0x71,
  0xb3, 0xef, 0xbe, 0x9e, 0x0a, 0xd9, 0xff, 0x6b, 0xb1, 0xe7, 0x44, 0x76,
  0xe9, 0xee, 0xc1, 0x3e, 0xa7, 0xe9, 0xf4, 0x5c, 0xed, 0x59, 0xf6, 0x60,
  0xfd, 0xe6, 0x27, 0x11, 0x60, 0xec, 0x07, 0x73, 0x8a, 0xca, 0xf8, 0x52,
  0x42, 0xe3, 0x3f, 0xa5, 0x46, 0x07, 0xf8, 0x2c, 0xf8, 0x6e, 0x3e, 0x83,
  0xb9, 0x30, 0x8b, 0x7d, 0xe6, 0x13, 0x74, 0xe2, 0x77, 0x69, 0xdb, 0x2f,
  0xe4, 0x9c, 0xca, 0x6a, 0x05, 0x9d, 0x7c, 0x7b, 0x89, 0x36, 0xd4, 0x71,
  0x62, 0x46, 0x1b, 0x7c, 0x9f, 0x65, 0x59, 0xd2, 0x43, 0x7a, 0xc9, 0x1d,
  0x47, 0x3e, 0x16, 0x84, 0x5e, 0x84, 0x5e, 0xcc, 0xe8, 0x05, 0xe8, 0x85,
  0x8c, 0x6e, 0x41, 0xb7, 0x32, 0x7a, 0x19, 0x7a, 0xd9, 0x6a, 0x3b, 0xbf,
  0x1b, 0xaf, 0xa7, 0xcd, 0xbf, 0xce, 0xfa, 0xb1, 0x90, 0xef, 0x71, 0x30,
  0xe4, 0x7b, 0x1c, 0x0c, 0xf9, 0x1e, 0x73, 0x72, 0x72, 0x72, 0x72, 0x1e,
  0x1a, 0xcf, 0xd9, 0x0a, 0xbc, 0xca, 0x65, 0x60, 0xcc, 0x46, 0xe0, 0x9b,
  0xcd, 0x40, 0xcc, 0xe7, 0x5e, 0xd1, 0x5c, 0x04, 0x22, 0xa5, 0x50, 0x54,
  0x2d, 0x54, 0x52, 0x0e, 0x95, 0xaa, 0x87, 0x3b, 0x53, 0xf2, 0x29, 0x32,
  0xed, 0x40, 0xce, 0x22, 0xd9, 0xab, 0x6e, 0x04, 0xed, 0xea, 0x66, 0xe0,
  0x39, 0x97, 0xef, 0xd7, 0xa5, 0xd3, 0x15, 0xd7, 0x3f, 0xd3, 0xa8, 0x54,
  0x57, 0xdc, 0x4e, 0x57, 0xa9, 0xf9, 0xaf, 0x0a, 0x75, 0xa0, 0x46, 0xd4,
  0xac, 0x07, 0x11, 0x59, 0x17, 0x46, 0x5a, 0x0f, 0xbf, 0x3a, 0x38, 0x6d,
  0x44, 0x8e, 0x93, 0x44, 0x5c, 0xdf, 0x18, 0x55, 0xb3, 0xe4, 0xe9, 0xa6,
  0xe3, 0x49, 0xb3, 0xe2, 0xa1, 0x96, 0xbc, 0x55, 0x8b, 0x8a, 0xb4, 0xbb,
  0x63, 0x0c, 0x0a, 0x85, 0xaa, 0xc8, 0x14, 0x1d, 0x61, 0x9f, 0xd2, 0x0e,
  0xeb, 0xe2, 0xeb, 0xeb, 0x62, 0x3c, 0x3c, 0x29, 0x8c, 0x5b, 0x74, 0xd7,
  0x94, 0x6e, 0xe7, 0x5a, 0x76, 0xd3, 0xfb, 0xca, 0x24, 0xac, 0x0c, 0x2b,
  0xe2, 0xa6, 0xca, 0x3a, 0x5b, 0xc5, 0x15, 0x77, 0x82, 0x13, 0xdf, 0x66,
  0x44, 0xf6, 0xab, 0xd1, 0x8f, 0x3f, 0x23, 0xdf, 0x7e, 0x5e, 0x3c, 0x3f,
  0x3f, 0xfd, 0xfe, 0xfa, 0x64, 0xe2, 0x0a, 0xcc, 0x76, 0x8d, 0x9a, 0x00,
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
