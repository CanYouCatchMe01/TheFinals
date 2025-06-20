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
; shader debug name: C:\Users\marcu\Downloads\DirectXTK12-main\DirectXTK12-main\Src/Shaders/Compiled\XboxGamingXboxOnePostProcess_PSSepia.pdb
; shader hash: 2ac12f66f40c5895a53b58f9101aecf0
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
; EntryFunctionName: PSSepia
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

define void @PSSepia() {
  %1 = call %dx.types.Handle @dx.op.createHandle(i32 57, i8 0, i32 0, i32 0, i1 false)  ; CreateHandle(resourceClass,rangeId,index,nonUniformIndex)
  %2 = call %dx.types.Handle @dx.op.createHandle(i32 57, i8 3, i32 0, i32 0, i1 false)  ; CreateHandle(resourceClass,rangeId,index,nonUniformIndex)
  %3 = call float @dx.op.loadInput.f32(i32 4, i32 1, i32 0, i8 0, i32 undef)  ; LoadInput(inputSigId,rowIndex,colIndex,gsVertexAxis)
  %4 = call float @dx.op.loadInput.f32(i32 4, i32 1, i32 0, i8 1, i32 undef)  ; LoadInput(inputSigId,rowIndex,colIndex,gsVertexAxis)
  %5 = call %dx.types.ResRet.f32 @dx.op.sample.f32(i32 60, %dx.types.Handle %1, %dx.types.Handle %2, float %3, float %4, float undef, float undef, i32 0, i32 0, i32 undef, float undef)  ; Sample(srv,sampler,coord0,coord1,coord2,coord3,offset0,offset1,offset2,clamp)
  %6 = extractvalue %dx.types.ResRet.f32 %5, 0
  %7 = extractvalue %dx.types.ResRet.f32 %5, 1
  %8 = extractvalue %dx.types.ResRet.f32 %5, 2
  %9 = extractvalue %dx.types.ResRet.f32 %5, 3
  %10 = call float @dx.op.dot3.f32(i32 55, float %6, float %7, float %8, float 0x3FD926E980000000, float 0x3FE89BA5E0000000, float 0x3FC83126E0000000)  ; Dot3(ax,ay,az,bx,by,bz)
  %11 = call float @dx.op.dot3.f32(i32 55, float %6, float %7, float %8, float 0x3FD6560420000000, float 0x3FE5F3B640000000, float 0x3FC5810620000000)  ; Dot3(ax,ay,az,bx,by,bz)
  %12 = call float @dx.op.dot3.f32(i32 55, float %6, float %7, float %8, float 0x3FD16872C0000000, float 0x3FE1168720000000, float 0x3FC0C49BA0000000)  ; Dot3(ax,ay,az,bx,by,bz)
  call void @dx.op.storeOutput.f32(i32 5, i32 0, i32 0, i8 0, float %10)  ; StoreOutput(outputSigId,rowIndex,colIndex,value)
  call void @dx.op.storeOutput.f32(i32 5, i32 0, i32 0, i8 1, float %11)  ; StoreOutput(outputSigId,rowIndex,colIndex,value)
  call void @dx.op.storeOutput.f32(i32 5, i32 0, i32 0, i8 2, float %12)  ; StoreOutput(outputSigId,rowIndex,colIndex,value)
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
declare float @dx.op.dot3.f32(i32, float, float, float, float, float, float) #0

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
!12 = !{void ()* @PSSepia, !"PSSepia", !13, !5, null}
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
  s_mov_b64     s[6:7], exec
  s_wqm_b64     exec, exec // wrscc
  s_mov_b32     s2, s3
  s_mov_b32     s3, 0
  s_load_dwordx8  s[8:15], s[2:3], 0x00
  s_mov_b32     m0, s4
  v_interp_p1_f32  v2, v0, attr0.x
  v_interp_p1_f32  v3, v0, attr0.y
  v_interp_p2_f32  v2, v1, attr0.x
  v_interp_p2_f32  v3, v1, attr0.y
  s_movk_i32    s0, 0x3092
  s_mov_b32     s1, 0x00fff000
  s_mov_b32     s2, 0x78500000
  s_brev_b32    s3, 1
  s_and_b64     exec, exec, s[6:7] // wrscc
  s_waitcnt     lgkmcnt(0)
  image_sample  v[0:3], v[2:3], s[8:15], s[0:3] dmask:0xf
  s_mov_b32     s0, 0x3ec9374c
  s_mov_b32     s3, 0x3eb2b021
  s_mov_b32     s5, 0x3e8b4396
  s_mov_b32     s1, 0x3e418937
  s_mov_b32     s2, 0x3e2c0831
  s_mov_b32     s4, 0x3e0624dd
  s_waitcnt     vmcnt(0)
  v_mul_legacy_f32  v4, 0x3f2f9db2, v1
  v_mul_legacy_f32  v5, 0x3f08b439, v1
  v_mul_legacy_f32  v1, 0x3f44dd2f, v1
  v_mac_legacy_f32  v4, s3, v0
  v_mac_legacy_f32  v5, s5, v0
  v_mad_legacy_f32  v0, v0, s0, v1
  v_mac_legacy_f32  v4, s2, v2
  v_mac_legacy_f32  v5, s4, v2
  v_mad_legacy_f32  v2, v2, s1, v0
  v_cvt_pkrtz_f16_f32  v0, v2, v4
  v_cvt_pkrtz_f16_f32  v1, v5, v3
  exp           mrt0, v0, v0, v1, v1 done compr vm
  s_endpgm      
end


NumVGPR=6,NumSGPR=18,LDS=0,Scratch=0,Occpancy=10


#endif

const unsigned char PostProcess_PSSepia[] = {
  0x44, 0x58, 0x42, 0x43, 0x6b, 0xc6, 0x21, 0x53, 0x08, 0x33, 0x6e, 0xd5,
  0xf4, 0x82, 0xd5, 0xd6, 0x2e, 0x9f, 0x91, 0x35, 0x01, 0x00, 0x00, 0x00,
  0xf8, 0x0d, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00,
  0x50, 0x00, 0x00, 0x00, 0xb8, 0x00, 0x00, 0x00, 0xf4, 0x00, 0x00, 0x00,
  0xe0, 0x01, 0x00, 0x00, 0x5c, 0x02, 0x00, 0x00, 0xe4, 0x02, 0x00, 0x00,
  0x00, 0x03, 0x00, 0x00, 0x53, 0x46, 0x49, 0x30, 0x08, 0x00, 0x00, 0x00,
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
  0x43, 0x4f, 0x4f, 0x52, 0x44, 0x00, 0x50, 0x53, 0x53, 0x65, 0x70, 0x69,
  0x61, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x01, 0x00, 0x44, 0x03, 0x03, 0x04, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x42, 0x00, 0x03, 0x02, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x44, 0x10,
  0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00,
  0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x52, 0x54, 0x53, 0x30, 0x74, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x01, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x40, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x05, 0x00, 0x00, 0x00, 0x24, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x2c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff,
  0x15, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
  0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
  0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xff, 0xff, 0x7f, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x05, 0x00, 0x00, 0x00, 0x49, 0x4c, 0x44, 0x4e, 0x80, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x78, 0x00, 0x43, 0x3a, 0x5c, 0x55, 0x73, 0x65, 0x72, 0x73,
  0x5c, 0x6d, 0x61, 0x72, 0x63, 0x75, 0x5c, 0x44, 0x6f, 0x77, 0x6e, 0x6c,
  0x6f, 0x61, 0x64, 0x73, 0x5c, 0x44, 0x69, 0x72, 0x65, 0x63, 0x74, 0x58,
  0x54, 0x4b, 0x31, 0x32, 0x2d, 0x6d, 0x61, 0x69, 0x6e, 0x5c, 0x44, 0x69,
  0x72, 0x65, 0x63, 0x74, 0x58, 0x54, 0x4b, 0x31, 0x32, 0x2d, 0x6d, 0x61,
  0x69, 0x6e, 0x5c, 0x53, 0x72, 0x63, 0x2f, 0x53, 0x68, 0x61, 0x64, 0x65,
  0x72, 0x73, 0x2f, 0x43, 0x6f, 0x6d, 0x70, 0x69, 0x6c, 0x65, 0x64, 0x5c,
  0x58, 0x62, 0x6f, 0x78, 0x47, 0x61, 0x6d, 0x69, 0x6e, 0x67, 0x58, 0x62,
  0x6f, 0x78, 0x4f, 0x6e, 0x65, 0x50, 0x6f, 0x73, 0x74, 0x50, 0x72, 0x6f,
  0x63, 0x65, 0x73, 0x73, 0x5f, 0x50, 0x53, 0x53, 0x65, 0x70, 0x69, 0x61,
  0x2e, 0x70, 0x64, 0x62, 0x00, 0x00, 0x00, 0x00, 0x48, 0x41, 0x53, 0x48,
  0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2a, 0xc1, 0x2f, 0x66,
  0xf4, 0x0c, 0x58, 0x95, 0xa5, 0x3b, 0x58, 0xf9, 0x10, 0x1a, 0xec, 0xf0,
  0x44, 0x58, 0x49, 0x4c, 0xf0, 0x0a, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00,
  0xbc, 0x02, 0x00, 0x00, 0x44, 0x58, 0x49, 0x4c, 0x00, 0x01, 0x00, 0x00,
  0x7c, 0x00, 0x00, 0x00, 0x68, 0x07, 0x00, 0x00, 0x58, 0x44, 0x41, 0x54,
  0x06, 0x00, 0x00, 0x00, 0x24, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00,
  0x6c, 0x00, 0x00, 0x00, 0x80, 0x07, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
  0xec, 0x07, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xfc, 0x07, 0x00, 0x00, 0x1f, 0x02, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
  0x1c, 0x0a, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00,
  0x94, 0x0a, 0x00, 0x00, 0x48, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00,
  0xdc, 0x0a, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00,
  0xe0, 0x01, 0x00, 0x00, 0x44, 0x58, 0x49, 0x4c, 0x00, 0x01, 0x00, 0x00,
  0x10, 0x00, 0x00, 0x00, 0x68, 0x07, 0x00, 0x00, 0x42, 0x43, 0xc0, 0xde,
  0x21, 0x0c, 0x00, 0x00, 0xd7, 0x01, 0x00, 0x00, 0x0b, 0x82, 0x20, 0x00,
  0x02, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00, 0x07, 0x81, 0x23, 0x91,
  0x41, 0xc8, 0x04, 0x49, 0x06, 0x10, 0x32, 0x39, 0x92, 0x01, 0x84, 0x0c,
  0x25, 0x05, 0x08, 0x19, 0x1e, 0x04, 0x8b, 0x62, 0x80, 0x14, 0x45, 0x02,
  0x42, 0x92, 0x0b, 0x42, 0xa4, 0x10, 0x32, 0x14, 0x38, 0x08, 0x18, 0x4b,
  0x0a, 0x32, 0x52, 0x88, 0x48, 0x90, 0x14, 0x20, 0x43, 0x46, 0x88, 0xa5,
  0x00, 0x19, 0x32, 0x42, 0xe4, 0x48, 0x0e, 0x90, 0x91, 0x22, 0xc4, 0x50,
  0x41, 0x51, 0x81, 0x8c, 0xe1, 0x83, 0xe5, 0x8a, 0x04, 0x29, 0x46, 0x06,
  0x51, 0x18, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x1b, 0x8c, 0xe0, 0xff,
  0xff, 0xff, 0xff, 0x07, 0x40, 0x02, 0xa8, 0x0d, 0x84, 0xf0, 0xff, 0xff,
  0xff, 0xff, 0x03, 0x20, 0x6d, 0x30, 0x86, 0xff, 0xff, 0xff, 0xff, 0x1f,
  0x00, 0x09, 0xa8, 0x00, 0x49, 0x18, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
  0x13, 0x82, 0x60, 0x42, 0x20, 0x4c, 0x08, 0x06, 0x00, 0x00, 0x00, 0x00,
  0x89, 0x20, 0x00, 0x00, 0x45, 0x00, 0x00, 0x00, 0x32, 0x22, 0x48, 0x09,
  0x20, 0x64, 0x85, 0x04, 0x93, 0x22, 0xa4, 0x84, 0x04, 0x93, 0x22, 0xe3,
  0x84, 0xa1, 0x90, 0x14, 0x12, 0x4c, 0x8a, 0x8c, 0x0b, 0x84, 0xa4, 0x4c,
  0x10, 0x70, 0x23, 0x00, 0x25, 0x00, 0x14, 0x66, 0x00, 0xe6, 0x08, 0xc0,
  0x60, 0x8e, 0x00, 0x29, 0xc6, 0x20, 0x84, 0x14, 0x42, 0xa6, 0x18, 0x80,
  0x10, 0x52, 0x06, 0xa1, 0x9b, 0x86, 0xcb, 0x9f, 0xb0, 0x87, 0x90, 0xfc,
  0x95, 0x90, 0x56, 0x62, 0xf2, 0x8b, 0xdb, 0x46, 0xc5, 0x18, 0x63, 0x10,
  0x2a, 0xf7, 0x0c, 0x97, 0x3f, 0x61, 0x0f, 0x21, 0xf9, 0x21, 0xd0, 0x0c,
  0x0b, 0x81, 0x82, 0x55, 0x18, 0x45, 0x18, 0x1b, 0x63, 0x0c, 0x42, 0xc8,
  0xa0, 0x56, 0x90, 0x41, 0xc6, 0x18, 0x63, 0x0c, 0x7a, 0x73, 0x04, 0x41,
  0x31, 0x18, 0x29, 0x84, 0x44, 0x92, 0x03, 0x01, 0xc3, 0x08, 0xc4, 0x30,
  0x53, 0x1b, 0x8c, 0x03, 0x3b, 0x84, 0xc3, 0x3c, 0xcc, 0x83, 0x1b, 0xd0,
  0x42, 0x39, 0xe0, 0x03, 0x3d, 0xd4, 0x83, 0x3c, 0x94, 0x83, 0x1c, 0x90,
  0x02, 0x1f, 0xd8, 0x43, 0x39, 0x8c, 0x03, 0x3d, 0xbc, 0x83, 0x3c, 0xf0,
  0x81, 0x39, 0xb0, 0xc3, 0x3b, 0x84, 0x03, 0x3d, 0xb0, 0x01, 0x18, 0xd0,
  0x81, 0x1f, 0x80, 0x81, 0x1f, 0xe8, 0x81, 0x1e, 0xb4, 0x43, 0x3a, 0xc0,
  0xc3, 0x3c, 0xfc, 0x02, 0x3d, 0xe4, 0x03, 0x3c, 0x94, 0x03, 0x0a, 0xc8,
  0x4c, 0x62, 0x30, 0x0e, 0xec, 0x10, 0x0e, 0xf3, 0x30, 0x0f, 0x6e, 0x40,
  0x0b, 0xe5, 0x80, 0x0f, 0xf4, 0x50, 0x0f, 0xf2, 0x50, 0x0e, 0x72, 0x40,
  0x0a, 0x7c, 0x60, 0x0f, 0xe5, 0x30, 0x0e, 0xf4, 0xf0, 0x0e, 0xf2, 0xc0,
  0x07, 0xe6, 0xc0, 0x0e, 0xef, 0x10, 0x0e, 0xf4, 0xc0, 0x06, 0x60, 0x40,
  0x07, 0x7e, 0x00, 0x06, 0x7e, 0x80, 0x84, 0x6a, 0xe9, 0xde, 0x24, 0x4d,
  0x11, 0x25, 0x4c, 0x3e, 0x0b, 0x30, 0xcf, 0x42, 0x44, 0xec, 0x04, 0x4c,
  0x04, 0x0a, 0x08, 0xe5, 0x44, 0x20, 0x00, 0x00, 0x13, 0x16, 0x72, 0xc0,
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
  0x36, 0x04, 0xd9, 0x04, 0x41, 0x00, 0x78, 0x40, 0x4d, 0x4d, 0x95, 0xc1,
  0xa5, 0x85, 0x71, 0x99, 0xb2, 0xfa, 0x82, 0x7a, 0x9b, 0x4b, 0xa3, 0x4b,
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
  0x71, 0x20, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x06, 0x70, 0xa4, 0x2c,
  0x4b, 0x3c, 0x08, 0x60, 0x05, 0xd2, 0x70, 0xf9, 0xce, 0xe3, 0x0b, 0x11,
  0x01, 0x4c, 0x44, 0x08, 0x34, 0xc3, 0x42, 0x18, 0x81, 0x33, 0x5c, 0xbe,
  0xf3, 0xf8, 0x83, 0x33, 0xdd, 0x7e, 0x71, 0xdb, 0x16, 0x30, 0x0d, 0x97,
  0xef, 0x3c, 0xfe, 0xe2, 0x00, 0x83, 0xd8, 0x3c, 0xd4, 0xe4, 0x17, 0xb7,
  0x6d, 0x03, 0xd0, 0x70, 0xf9, 0xce, 0xe3, 0x4b, 0x00, 0xf3, 0x2c, 0x84,
  0x5f, 0xdc, 0xb6, 0x09, 0x54, 0xc3, 0xe5, 0x3b, 0x8f, 0x2f, 0x4d, 0x4e,
  0x44, 0xa0, 0xd4, 0xf4, 0x50, 0x93, 0x5f, 0xdc, 0x36, 0x00, 0x00, 0x00,
  0x61, 0x20, 0x00, 0x00, 0x47, 0x00, 0x00, 0x00, 0x13, 0x04, 0x41, 0x2c,
  0x10, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x14, 0x47, 0x00, 0xa8,
  0x94, 0x00, 0x91, 0xc2, 0x2b, 0x84, 0x92, 0x2b, 0xb7, 0x19, 0x80, 0x52,
  0xa0, 0x31, 0x46, 0x90, 0x87, 0x6d, 0x0c, 0x7f, 0x63, 0x04, 0xbd, 0x99,
  0xb2, 0xe0, 0x37, 0x46, 0x60, 0xf3, 0xb0, 0x8d, 0x7e, 0x63, 0x04, 0x71,
  0x28, 0xe2, 0xe2, 0x37, 0x46, 0x20, 0xb7, 0xe7, 0x2f, 0x7f, 0x63, 0x04,
  0x61, 0xc8, 0x96, 0xeb, 0x37, 0x46, 0x70, 0xa7, 0xe2, 0x48, 0x7e, 0x63,
  0x04, 0x6f, 0x7a, 0xa7, 0xf4, 0x37, 0x46, 0xc0, 0xea, 0xad, 0xcc, 0x7e,
  0x33, 0x00, 0x00, 0x00, 0x23, 0x06, 0x09, 0x00, 0x82, 0x60, 0x20, 0x91,
  0x81, 0x83, 0x89, 0x81, 0x18, 0x48, 0x23, 0x06, 0x09, 0x00, 0x82, 0x60,
  0x20, 0x95, 0xc1, 0xb3, 0x8d, 0xc1, 0x18, 0x4c, 0x23, 0x06, 0x09, 0x00,
  0x82, 0x60, 0x60, 0xa8, 0x41, 0x54, 0x06, 0x64, 0xa0, 0x39, 0x23, 0x06,
  0x09, 0x00, 0x82, 0x60, 0x60, 0xac, 0x81, 0x64, 0x06, 0x65, 0x40, 0x3d,
  0x23, 0x06, 0x0f, 0x00, 0x82, 0x60, 0xd0, 0xa8, 0x01, 0x45, 0x0c, 0x42,
  0x50, 0x14, 0x66, 0x60, 0x06, 0x50, 0x31, 0x9a, 0x10, 0x00, 0xa3, 0x09,
  0x42, 0x30, 0x9a, 0x30, 0x08, 0xa3, 0x09, 0xc4, 0x30, 0x62, 0xb0, 0x00,
  0x20, 0x08, 0x06, 0x8f, 0x1b, 0x58, 0xc4, 0x20, 0x2c, 0x4c, 0x33, 0x62,
  0xb0, 0x00, 0x20, 0x08, 0x06, 0xcf, 0x1b, 0x5c, 0x05, 0x31, 0x3c, 0x50,
  0x34, 0x62, 0xb0, 0x00, 0x20, 0x08, 0x06, 0x0f, 0x1c, 0x60, 0x46, 0x41,
  0x4c, 0x15, 0x35, 0x62, 0x90, 0x00, 0x20, 0x08, 0x06, 0xc8, 0x1c, 0x5c,
  0x6e, 0xe0, 0x06, 0x64, 0x30, 0x8c, 0x18, 0x24, 0x00, 0x08, 0x82, 0x01,
  0x32, 0x07, 0x97, 0x1b, 0xb8, 0x41, 0x27, 0x8c, 0x18, 0x24, 0x00, 0x08,
  0x82, 0x01, 0x32, 0x07, 0x97, 0x1b, 0xb8, 0xc1, 0x18, 0x04, 0x23, 0x06,
  0x09, 0x00, 0x82, 0x60, 0x80, 0xcc, 0xc1, 0xe5, 0x06, 0x6e, 0x60, 0x06,
  0x04, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2a, 0xc1, 0x2f, 0x66,
  0xf4, 0x0c, 0x58, 0x95, 0xa5, 0x3b, 0x58, 0xf9, 0x10, 0x1a, 0xec, 0xf0,
  0x17, 0x00, 0x01, 0x00, 0x29, 0x10, 0x0f, 0x00, 0x78, 0x01, 0xed, 0x97,
  0xbf, 0x6b, 0x14, 0x41, 0x14, 0xc7, 0xdf, 0xfc, 0xb8, 0xcd, 0xde, 0xba,
  0xb9, 0x3d, 0xc4, 0x42, 0x82, 0x85, 0x82, 0x8d, 0x12, 0xbc, 0x04, 0x84,
  0x20, 0x21, 0x77, 0x09, 0xa6, 0xd3, 0xc2, 0x32, 0x84, 0x10, 0x8e, 0x14,
  0x62, 0x29, 0x56, 0x56, 0xe7, 0x5e, 0x12, 0x95, 0xc4, 0x10, 0x42, 0x20,
  0x92, 0x26, 0x95, 0xda, 0x4a, 0x08, 0xb1, 0x52, 0xe6, 0x22, 0x58, 0x9c,
  0x9d, 0xd8, 0x59, 0x04, 0xfd, 0x03, 0x2c, 0xae, 0xb0, 0x50, 0x90, 0xac,
  0xdf, 0x37, 0xb7, 0xa3, 0x7b, 0x12, 0xb4, 0x89, 0xa0, 0xb8, 0x1f, 0xf8,
  0xbe, 0x37, 0xdf, 0xdb, 0x7d, 0xb3, 0x73, 0x37, 0x7b, 0xf0, 0xa6, 0x1c,
  0x91, 0xe5, 0xd6, 0xea, 0x87, 0xd3, 0x9c, 0x87, 0x1f, 0x5d, 0x79, 0x17,
  0xf7, 0x11, 0x15, 0x30, 0x16, 0x10, 0x67, 0x66, 0xb3, 0x9f, 0x23, 0xd1,
  0xe3, 0x12, 0x47, 0xa2, 0x80, 0x43, 0x8a, 0x07, 0x1d, 0x87, 0x98, 0x71,
  0x0e, 0x29, 0x5c, 0x4f, 0x14, 0x57, 0xa1, 0x1a, 0x8f, 0x7e, 0xe6, 0x04,
  0xc4, 0xd3, 0xa6, 0x53, 0xf7, 0xc0, 0xb5, 0xdd, 0xfa, 0x1f, 0x99, 0xc9,
  0x8e, 0x1d, 0x12, 0xe2, 0xcf, 0xb3, 0xd7, 0x34, 0x07, 0xf0, 0x6c, 0xf7,
  0x22, 0x9e, 0x4f, 0x93, 0x10, 0x2d, 0x8f, 0x5f, 0xb0, 0xeb, 0x98, 0x78,
  0x5a, 0x1c, 0xe3, 0x7c, 0xee, 0xf9, 0x7b, 0x9b, 0xff, 0x55, 0xb2, 0xdf,
  0xd7, 0xe1, 0xf6, 0x89, 0x79, 0xc3, 0xe1, 0x37, 0x28, 0x0e, 0xe0, 0x46,
  0xba, 0xaf, 0x6e, 0x2f, 0xf7, 0xa0, 0xc3, 0xe6, 0x67, 0x12, 0xc0, 0xf9,
  0x30, 0xb8, 0xc6, 0x13, 0x2a, 0x26, 0x1f, 0x83, 0xff, 0x14, 0xf7, 0xd5,
  0xf9, 0xb7, 0xe0, 0x77, 0xb3, 0x0c, 0xa5, 0x7f, 0x33, 0x8b, 0x7b, 0x37,
  0x2b, 0x1c, 0x28, 0x6e, 0xb1, 0xd6, 0x4e, 0xd2, 0x67, 0x76, 0xce, 0x0b,
  0x78, 0xae, 0x75, 0x5e, 0xb1, 0xb7, 0x85, 0x19, 0x8f, 0xcd, 0x93, 0x45,
  0x9a, 0x2d, 0xf4, 0xc9, 0xd9, 0xe8, 0x14, 0xea, 0xf1, 0x40, 0xf8, 0x19,
  0xf8, 0x99, 0x8c, 0x9f, 0x86, 0x9f, 0xce, 0xf8, 0x3a, 0x7c, 0x3d, 0xe3,
  0xe7, 0xe0, 0xe7, 0x9c, 0x77, 0xf3, 0x47, 0xf6, 0x79, 0x05, 0xf5, 0xab,
  0xbd, 0xfe, 0x5b, 0xc8, 0xd7, 0x78, 0x34, 0xe4, 0x6b, 0x3c, 0x1a, 0xf2,
  0x35, 0xe6, 0xe4, 0xe4, 0xe4, 0xe4, 0xfc, 0x69, 0x1a, 0xfa, 0x9e, 0x69,
  0x04, 0x07, 0x46, 0xa9, 0x79, 0x13, 0xab, 0x05, 0x43, 0xea, 0xd5, 0x9e,
  0x56, 0x5f, 0x0d, 0xba, 0xd0, 0x36, 0x89, 0xb0, 0x2d, 0xa8, 0xd8, 0x16,
  0xa2, 0xbf, 0xbd, 0x3e, 0x44, 0xdb, 0x89, 0x6a, 0x1a, 0xea, 0x24, 0x94,
  0xe0, 0x5e, 0xa2, 0x6b, 0xb7, 0x9b, 0xc7, 0x16, 0x4c, 0xc3, 0x3b, 0xb8,
  0x7f, 0x87, 0x56, 0x5a, 0x14, 0xc5, 0x1d, 0x89, 0x6e, 0x35, 0x51, 0xb1,
  0xb9, 0x3a, 0xf2, 0xba, 0x9a, 0x60, 0xae, 0x33, 0xdb, 0x3b, 0xc8, 0x77,
  0xcd, 0xc3, 0xcb, 0x0f, 0x90, 0x9b, 0x66, 0x64, 0x69, 0x02, 0x79, 0xde,
  0x0c, 0xfb, 0x83, 0xc8, 0x8b, 0x66, 0xff, 0xac, 0x57, 0xbd, 0x19, 0xad,
  0xb4, 0x12, 0xe9, 0x97, 0x76, 0xb6, 0x2a, 0xb5, 0x44, 0x06, 0xa5, 0x4b,
  0xbb, 0x3e, 0xb2, 0x2c, 0x55, 0xf6, 0x27, 0x6b, 0x8a, 0xfc, 0xb0, 0x40,
  0x41, 0x88, 0x7e, 0xf2, 0x2d, 0x09, 0xad, 0xa5, 0xf6, 0x43, 0xad, 0x83,
  0x50, 0xc2, 0xa3, 0x77, 0xd5, 0xe8, 0x3d, 0x7b, 0x7a, 0x57, 0xa2, 0x66,
  0x6b, 0x80, 0x93, 0xb0, 0xa7, 0x92, 0x21, 0x0e, 0x8c, 0xbd, 0xd4, 0x6d,
  0x9a, 0xeb, 0x1c, 0xbe, 0xe3, 0xf7, 0xde, 0xe7, 0x78, 0x91, 0x9e, 0x65,
  0x06, 0xa1, 0x22, 0xe4, 0xe1, 0x14, 0xcb, 0x3d, 0xb8, 0xb0, 0xdd, 0x78,
  0x17, 0x6d, 0x4f, 0x3a, 0x44, 0xe7, 0x5f, 0x56, 0xae, 0x7f, 0x0a, 0xa7,
  0x36, 0x9e, 0x8c, 0x4e, 0x7d, 0x29, 0x0f, 0x7c, 0xec, 0x7c, 0x03, 0x20,
  0x46, 0x9b, 0x5d, 0x00, 0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
  0x04, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x92, 0x30, 0x00, 0x00, 0x00, 0xf0, 0xff, 0x00, 0x00, 0x00, 0x50, 0x78,
  0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x03, 0x00,
  0x08, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x74, 0x00, 0x00,
  0x78, 0x01, 0x4d, 0xc8, 0x3b, 0x0a, 0x80, 0x40, 0x10, 0x04, 0xd1, 0xf6,
  0xb3, 0xb9, 0xc9, 0x82, 0x91, 0x91, 0xa1, 0x87, 0xf0, 0x66, 0x7b, 0xf4,
  0xb1, 0x0a, 0x14, 0x2c, 0x78, 0xf4, 0x30, 0x53, 0x12, 0xed, 0xef, 0xde,
  0x38, 0x60, 0x0d, 0x27, 0xfc, 0x5f, 0x30, 0xef, 0xaf, 0xa2, 0xce, 0x2e,
  0x3f, 0xb6, 0x61, 0xc5, 0x0c, 0xab, 0x1a, 0xc3, 0xb5, 0x96, 0xe4, 0x01,
  0x59, 0x4b, 0x08, 0x02, 0x78, 0x62, 0x6f, 0x70, 0x01, 0x00, 0x00, 0x00,
  0x7e, 0x02, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00
};
