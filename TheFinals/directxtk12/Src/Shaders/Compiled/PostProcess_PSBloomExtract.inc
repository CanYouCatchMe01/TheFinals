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
; shader debug name: C:\Users\marcu\Downloads\DirectXTK12-main\DirectXTK12-main\Src/Shaders/Compiled\PostProcess_PSBloomExtract.pdb
; shader hash: 49c78433cc1bb43d427dcdb95d7f4b6b
;
; Pipeline Runtime Information: 
;
; Pixel Shader
; DepthOutput=0
; SampleFrequency=0
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
;   [512 x i8] (type annotation not present)
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
target triple = "dxil-ms-dx"

%dx.types.Handle = type { i8* }
%dx.types.ResRet.f32 = type { float, float, float, float, i32 }
%dx.types.CBufRet.f32 = type { float, float, float, float }
%"class.Texture2D<vector<float, 4> >" = type { <4 x float>, %"class.Texture2D<vector<float, 4> >::mips_type" }
%"class.Texture2D<vector<float, 4> >::mips_type" = type { i32 }
%Parameters = type { [16 x <4 x float>], [16 x <4 x float>] }
%struct.SamplerState = type { i32 }

define void @PSBloomExtract() {
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
  %11 = call %dx.types.CBufRet.f32 @dx.op.cbufferLoadLegacy.f32(i32 59, %dx.types.Handle %3, i32 16)  ; CBufferLoadLegacy(handle,regIndex)
  %12 = extractvalue %dx.types.CBufRet.f32 %11, 0
  %13 = extractvalue %dx.types.CBufRet.f32 %11, 1
  %14 = extractvalue %dx.types.CBufRet.f32 %11, 2
  %15 = extractvalue %dx.types.CBufRet.f32 %11, 3
  %16 = fsub fast float %7, %12
  %17 = fsub fast float %8, %13
  %18 = fsub fast float %9, %14
  %19 = fsub fast float %10, %15
  %20 = fsub fast float 1.000000e+00, %12
  %21 = fsub fast float 1.000000e+00, %13
  %22 = fsub fast float 1.000000e+00, %14
  %23 = fsub fast float 1.000000e+00, %15
  %24 = fdiv fast float %16, %20
  %25 = fdiv fast float %17, %21
  %26 = fdiv fast float %18, %22
  %27 = fdiv fast float %19, %23
  %28 = call float @dx.op.unary.f32(i32 7, float %24)  ; Saturate(value)
  %29 = call float @dx.op.unary.f32(i32 7, float %25)  ; Saturate(value)
  %30 = call float @dx.op.unary.f32(i32 7, float %26)  ; Saturate(value)
  %31 = call float @dx.op.unary.f32(i32 7, float %27)  ; Saturate(value)
  call void @dx.op.storeOutput.f32(i32 5, i32 0, i32 0, i8 0, float %28)  ; StoreOutput(outputSigId,rowIndex,colIndex,value)
  call void @dx.op.storeOutput.f32(i32 5, i32 0, i32 0, i8 1, float %29)  ; StoreOutput(outputSigId,rowIndex,colIndex,value)
  call void @dx.op.storeOutput.f32(i32 5, i32 0, i32 0, i8 2, float %30)  ; StoreOutput(outputSigId,rowIndex,colIndex,value)
  call void @dx.op.storeOutput.f32(i32 5, i32 0, i32 0, i8 3, float %31)  ; StoreOutput(outputSigId,rowIndex,colIndex,value)
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

!llvm.ident = !{!0}
!dx.version = !{!1}
!dx.valver = !{!2}
!dx.shaderModel = !{!3}
!dx.resources = !{!4}
!dx.viewIdState = !{!12}
!dx.entryPoints = !{!13}

!0 = !{!"clang version 3.7 (tags/RELEASE_370/final)"}
!1 = !{i32 1, i32 0}
!2 = !{i32 1, i32 6}
!3 = !{!"ps", i32 6, i32 0}
!4 = !{!5, null, !8, !10}
!5 = !{!6}
!6 = !{i32 0, %"class.Texture2D<vector<float, 4> >"* undef, !"", i32 0, i32 0, i32 1, i32 2, i32 0, !7}
!7 = !{i32 0, i32 9}
!8 = !{!9}
!9 = !{i32 0, %Parameters* undef, !"", i32 0, i32 0, i32 1, i32 512, null}
!10 = !{!11}
!11 = !{i32 0, %struct.SamplerState* undef, !"", i32 0, i32 0, i32 1, i32 0, null}
!12 = !{[8 x i32] [i32 6, i32 4, i32 0, i32 0, i32 0, i32 0, i32 15, i32 15]}
!13 = !{void ()* @PSBloomExtract, !"PSBloomExtract", !14, !4, null}
!14 = !{!15, !20, null}
!15 = !{!16, !18}
!16 = !{i32 0, !"SV_Position", i8 9, i8 3, !17, i8 4, i32 1, i8 4, i32 0, i8 0, null}
!17 = !{i32 0}
!18 = !{i32 1, !"TEXCOORD", i8 9, i8 0, !17, i8 2, i32 1, i8 2, i32 1, i8 0, !19}
!19 = !{i32 3, i32 3}
!20 = !{!21}
!21 = !{i32 0, !"SV_Target", i8 9, i8 16, !17, i8 0, i32 1, i8 4, i32 0, i8 0, !22}
!22 = !{i32 3, i32 15}

#endif

const unsigned char PostProcess_PSBloomExtract[] = {
  0x44, 0x58, 0x42, 0x43, 0x4e, 0x8a, 0x80, 0x3b, 0x7a, 0x53, 0xfe, 0x9d,
  0xff, 0x7a, 0x63, 0xc4, 0x61, 0x19, 0x18, 0x1c, 0x01, 0x00, 0x00, 0x00,
  0xeb, 0x0a, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00,
  0x50, 0x00, 0x00, 0x00, 0xb5, 0x00, 0x00, 0x00, 0xef, 0x00, 0x00, 0x00,
  0xe7, 0x01, 0x00, 0x00, 0x7f, 0x02, 0x00, 0x00, 0xfb, 0x02, 0x00, 0x00,
  0x17, 0x03, 0x00, 0x00, 0x53, 0x46, 0x49, 0x30, 0x08, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x49, 0x53, 0x47, 0x31,
  0x5d, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x48, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x01, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x54, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x03, 0x03, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x53, 0x56, 0x5f, 0x50, 0x6f, 0x73, 0x69, 0x74,
  0x69, 0x6f, 0x6e, 0x00, 0x54, 0x45, 0x58, 0x43, 0x4f, 0x4f, 0x52, 0x44,
  0x00, 0x4f, 0x53, 0x47, 0x31, 0x32, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00,
  0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x53, 0x56, 0x5f, 0x54, 0x61, 0x72, 0x67, 0x65, 0x74, 0x00, 0x50,
  0x53, 0x56, 0x30, 0xf0, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00,
  0x00, 0x00, 0x00, 0x02, 0x01, 0x00, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03,
  0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0d,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x00,
  0x54, 0x45, 0x58, 0x43, 0x4f, 0x4f, 0x52, 0x44, 0x00, 0x00, 0x00, 0x01,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x44, 0x03, 0x03,
  0x04, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
  0x01, 0x42, 0x00, 0x03, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x01, 0x00, 0x44, 0x10, 0x03, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x52, 0x54, 0x53, 0x30, 0x90,
  0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x18,
  0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x5c, 0x00, 0x00, 0x00, 0x1e,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x30,
  0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x50,
  0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x15,
  0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x03,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x04,
  0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff,
  0xff, 0x7f, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05,
  0x00, 0x00, 0x00, 0x49, 0x4c, 0x44, 0x4e, 0x74, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x6e, 0x00, 0x43, 0x3a, 0x5c, 0x55, 0x73, 0x65, 0x72, 0x73, 0x5c,
  0x6d, 0x61, 0x72, 0x63, 0x75, 0x5c, 0x44, 0x6f, 0x77, 0x6e, 0x6c, 0x6f,
  0x61, 0x64, 0x73, 0x5c, 0x44, 0x69, 0x72, 0x65, 0x63, 0x74, 0x58, 0x54,
  0x4b, 0x31, 0x32, 0x2d, 0x6d, 0x61, 0x69, 0x6e, 0x5c, 0x44, 0x69, 0x72,
  0x65, 0x63, 0x74, 0x58, 0x54, 0x4b, 0x31, 0x32, 0x2d, 0x6d, 0x61, 0x69,
  0x6e, 0x5c, 0x53, 0x72, 0x63, 0x2f, 0x53, 0x68, 0x61, 0x64, 0x65, 0x72,
  0x73, 0x2f, 0x43, 0x6f, 0x6d, 0x70, 0x69, 0x6c, 0x65, 0x64, 0x5c, 0x50,
  0x6f, 0x73, 0x74, 0x50, 0x72, 0x6f, 0x63, 0x65, 0x73, 0x73, 0x5f, 0x50,
  0x53, 0x42, 0x6c, 0x6f, 0x6f, 0x6d, 0x45, 0x78, 0x74, 0x72, 0x61, 0x63,
  0x74, 0x2e, 0x70, 0x64, 0x62, 0x00, 0x00, 0x48, 0x41, 0x53, 0x48, 0x14,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x49, 0xc7, 0x84, 0x33, 0xcc,
  0x1b, 0xb4, 0x3d, 0x42, 0x7d, 0xcd, 0xb9, 0x5d, 0x7f, 0x4b, 0x6b, 0x44,
  0x58, 0x49, 0x4c, 0xcc, 0x07, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0xf3,
  0x01, 0x00, 0x00, 0x44, 0x58, 0x49, 0x4c, 0x00, 0x01, 0x00, 0x00, 0x10,
  0x00, 0x00, 0x00, 0xb4, 0x07, 0x00, 0x00, 0x42, 0x43, 0xc0, 0xde, 0x21,
  0x0c, 0x00, 0x00, 0xea, 0x01, 0x00, 0x00, 0x0b, 0x82, 0x20, 0x00, 0x02,
  0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00, 0x07, 0x81, 0x23, 0x91, 0x41,
  0xc8, 0x04, 0x49, 0x06, 0x10, 0x32, 0x39, 0x92, 0x01, 0x84, 0x0c, 0x25,
  0x05, 0x08, 0x19, 0x1e, 0x04, 0x8b, 0x62, 0x80, 0x18, 0x45, 0x02, 0x42,
  0x92, 0x0b, 0x42, 0xc4, 0x10, 0x32, 0x14, 0x38, 0x08, 0x18, 0x4b, 0x0a,
  0x32, 0x62, 0x88, 0x48, 0x90, 0x14, 0x20, 0x43, 0x46, 0x88, 0xa5, 0x00,
  0x19, 0x32, 0x42, 0xe4, 0x48, 0x0e, 0x90, 0x11, 0x23, 0xc4, 0x50, 0x41,
  0x51, 0x81, 0x8c, 0xe1, 0x83, 0xe5, 0x8a, 0x04, 0x31, 0x46, 0x06, 0x51,
  0x18, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x1b, 0x8c, 0xe0, 0xff, 0xff,
  0xff, 0xff, 0x07, 0x40, 0x02, 0xa8, 0x0d, 0x84, 0xf0, 0xff, 0xff, 0xff,
  0xff, 0x03, 0x20, 0x6d, 0x30, 0x86, 0xff, 0xff, 0xff, 0xff, 0x1f, 0x00,
  0x09, 0xa8, 0x00, 0x49, 0x18, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x13,
  0x82, 0x60, 0x42, 0x20, 0x4c, 0x08, 0x06, 0x00, 0x00, 0x00, 0x00, 0x89,
  0x20, 0x00, 0x00, 0x51, 0x00, 0x00, 0x00, 0x32, 0x22, 0x88, 0x09, 0x20,
  0x64, 0x85, 0x04, 0x13, 0x23, 0xa4, 0x84, 0x04, 0x13, 0x23, 0xe3, 0x84,
  0xa1, 0x90, 0x14, 0x12, 0x4c, 0x8c, 0x8c, 0x0b, 0x84, 0xc4, 0x4c, 0x10,
  0x88, 0xc1, 0x08, 0x40, 0x09, 0x00, 0x0a, 0x66, 0x00, 0xe6, 0x08, 0xc0,
  0x60, 0x8e, 0x00, 0x29, 0xc6, 0x40, 0x10, 0x44, 0x41, 0x90, 0x51, 0x0c,
  0x80, 0x20, 0x88, 0x62, 0x20, 0xe4, 0xa6, 0xe1, 0xf2, 0x27, 0xec, 0x21,
  0x24, 0x7f, 0x25, 0xa4, 0x95, 0x98, 0xfc, 0xe2, 0xb6, 0x51, 0x31, 0x0c,
  0xc3, 0x40, 0x50, 0x71, 0xcf, 0x70, 0xf9, 0x13, 0xf6, 0x10, 0x92, 0x1f,
  0x02, 0xcd, 0xb0, 0x10, 0x28, 0x58, 0x0a, 0xa3, 0x10, 0x0c, 0x33, 0x0c,
  0xc3, 0x40, 0x10, 0xc4, 0x40, 0x4d, 0x19, 0x06, 0x62, 0xa0, 0xe7, 0xa8,
  0xe1, 0xf2, 0x27, 0xec, 0x21, 0x24, 0x9f, 0xdb, 0xa8, 0x62, 0x25, 0x26,
  0xbf, 0xb8, 0x6d, 0x44, 0x0c, 0xc3, 0x30, 0x14, 0x22, 0x22, 0x18, 0x82,
  0xa4, 0x39, 0x82, 0xa0, 0x18, 0x0c, 0x51, 0x10, 0x04, 0x45, 0xd5, 0x40,
  0xc0, 0x30, 0x02, 0x31, 0xcc, 0xd4, 0x06, 0xe3, 0xc0, 0x0e, 0xe1, 0x30,
  0x0f, 0xf3, 0xe0, 0x06, 0xb4, 0x50, 0x0e, 0xf8, 0x40, 0x0f, 0xf5, 0x20,
  0x0f, 0xe5, 0x20, 0x07, 0xa4, 0xc0, 0x07, 0xf6, 0x50, 0x0e, 0xe3, 0x40,
  0x0f, 0xef, 0x20, 0x0f, 0x7c, 0x60, 0x0e, 0xec, 0xf0, 0x0e, 0xe1, 0x40,
  0x0f, 0x6c, 0x00, 0x06, 0x74, 0xe0, 0x07, 0x60, 0xe0, 0x07, 0x7a, 0xa0,
  0x07, 0xed, 0x90, 0x0e, 0xf0, 0x30, 0x0f, 0xbf, 0x40, 0x0f, 0xf9, 0x00,
  0x0f, 0xe5, 0x80, 0x02, 0x62, 0x26, 0x31, 0x18, 0x07, 0x76, 0x08, 0x87,
  0x79, 0x98, 0x07, 0x37, 0xa0, 0x85, 0x72, 0xc0, 0x07, 0x7a, 0xa8, 0x07,
  0x79, 0x28, 0x07, 0x39, 0x20, 0x05, 0x3e, 0xb0, 0x87, 0x72, 0x18, 0x07,
  0x7a, 0x78, 0x07, 0x79, 0xe0, 0x03, 0x73, 0x60, 0x87, 0x77, 0x08, 0x07,
  0x7a, 0x60, 0x03, 0x30, 0xa0, 0x03, 0x3f, 0x00, 0x03, 0x3f, 0x40, 0x02,
  0x96, 0x91, 0x96, 0x10, 0xd8, 0x29, 0x29, 0x10, 0x01, 0x0c, 0x31, 0x11,
  0x91, 0x84, 0x04, 0x8e, 0xa3, 0xee, 0x26, 0x69, 0x8a, 0x28, 0x61, 0xf2,
  0x59, 0x80, 0x79, 0x16, 0x22, 0x62, 0x27, 0x60, 0x22, 0x50, 0x40, 0xd0,
  0x97, 0x08, 0x04, 0x00, 0x00, 0x00, 0x00, 0x13, 0x14, 0x72, 0xc0, 0x87,
  0x74, 0x60, 0x87, 0x36, 0x68, 0x87, 0x79, 0x68, 0x03, 0x72, 0xc0, 0x87,
  0x0d, 0xaf, 0x50, 0x0e, 0x6d, 0xd0, 0x0e, 0x7a, 0x50, 0x0e, 0x6d, 0x00,
  0x0f, 0x7a, 0x30, 0x07, 0x72, 0xa0, 0x07, 0x73, 0x20, 0x07, 0x6d, 0x90,
  0x0e, 0x71, 0xa0, 0x07, 0x73, 0x20, 0x07, 0x6d, 0x90, 0x0e, 0x78, 0xa0,
  0x07, 0x73, 0x20, 0x07, 0x6d, 0x90, 0x0e, 0x71, 0x60, 0x07, 0x7a, 0x30,
  0x07, 0x72, 0xd0, 0x06, 0xe9, 0x30, 0x07, 0x72, 0xa0, 0x07, 0x73, 0x20,
  0x07, 0x6d, 0x90, 0x0e, 0x76, 0x40, 0x07, 0x7a, 0x60, 0x07, 0x74, 0xd0,
  0x06, 0xe6, 0x10, 0x07, 0x76, 0xa0, 0x07, 0x73, 0x20, 0x07, 0x6d, 0x60,
  0x0e, 0x73, 0x20, 0x07, 0x7a, 0x30, 0x07, 0x72, 0xd0, 0x06, 0xe6, 0x60,
  0x07, 0x74, 0xa0, 0x07, 0x76, 0x40, 0x07, 0x6d, 0xe0, 0x0e, 0x78, 0xa0,
  0x07, 0x71, 0x60, 0x07, 0x7a, 0x30, 0x07, 0x72, 0xa0, 0x07, 0x76, 0x40,
  0x07, 0x43, 0x9e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x86, 0x3c, 0x06, 0x10, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x0c, 0x79, 0x10, 0x20, 0x00, 0x04, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x18, 0xf2, 0x34, 0x40, 0x00, 0x0c, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0xe4, 0x79, 0x80, 0x00, 0x08, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0xc8, 0x23, 0x01, 0x01, 0x30,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x90, 0xa7, 0x02, 0x02,
  0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x2c, 0x10, 0x0f,
  0x00, 0x00, 0x00, 0x32, 0x1e, 0x98, 0x14, 0x19, 0x11, 0x4c, 0x90, 0x8c,
  0x09, 0x26, 0x47, 0xc6, 0x04, 0x43, 0x22, 0x4a, 0x60, 0x04, 0xa0, 0x18,
  0x8a, 0xa0, 0x24, 0x0a, 0x10, 0xa1, 0x0c, 0xca, 0x83, 0x8a, 0x92, 0x28,
  0x83, 0x42, 0x18, 0x01, 0x28, 0x82, 0x02, 0xa1, 0x6d, 0x06, 0x80, 0xbc,
  0x19, 0x00, 0x02, 0x67, 0x00, 0x28, 0x1c, 0x0b, 0x31, 0x08, 0x00, 0x00,
  0x80, 0xe7, 0x01, 0x79, 0x18, 0x00, 0x00, 0x67, 0x00, 0x00, 0x00, 0x1a,
  0x03, 0x4c, 0x90, 0x46, 0x02, 0x13, 0x44, 0x35, 0x18, 0x63, 0x0b, 0x73,
  0x3b, 0x03, 0xb1, 0x2b, 0x93, 0x9b, 0x4b, 0x7b, 0x73, 0x03, 0x99, 0x71,
  0xb9, 0x01, 0x41, 0xa1, 0x0b, 0x3b, 0x9b, 0x7b, 0x91, 0x2a, 0x62, 0x2a,
  0x0a, 0x9a, 0x2a, 0xfa, 0x9a, 0xb9, 0x81, 0x79, 0x31, 0x4b, 0x73, 0x0b,
  0x63, 0x4b, 0xd9, 0x10, 0x04, 0x13, 0x04, 0xe2, 0x98, 0x20, 0x10, 0xc8,
  0x06, 0x61, 0x20, 0x26, 0x08, 0x44, 0xb2, 0x41, 0x18, 0x0c, 0x0a, 0x70,
  0x73, 0x1b, 0x06, 0xc4, 0x20, 0x26, 0x08, 0x5b, 0x45, 0x60, 0x82, 0x40,
  0x28, 0x13, 0x04, 0x62, 0xd9, 0x20, 0x10, 0xcd, 0x86, 0x84, 0x50, 0x16,
  0x82, 0x18, 0x18, 0xc2, 0xd9, 0x10, 0x3c, 0x13, 0x04, 0xcf, 0x9a, 0x20,
  0x10, 0xcc, 0x06, 0x84, 0x88, 0x16, 0x82, 0x18, 0x24, 0x60, 0x43, 0x30,
  0x4d, 0x10, 0xc0, 0xe0, 0xda, 0x80, 0x10, 0xd5, 0x42, 0x10, 0x03, 0x01,
  0x6c, 0x08, 0xac, 0x0d, 0x04, 0x04, 0x50, 0xd7, 0x04, 0x21, 0x0c, 0xb0,
  0x0d, 0x41, 0x36, 0x41, 0x10, 0x00, 0x3a, 0x50, 0x53, 0x42, 0x6c, 0x6f,
  0x6f, 0x6d, 0x45, 0x78, 0x74, 0x72, 0x61, 0x63, 0x74, 0x5c, 0xa6, 0xac,
  0xbe, 0xa0, 0xde, 0xe6, 0xd2, 0xe8, 0xd2, 0xde, 0xdc, 0x26, 0x08, 0xc5,
  0x33, 0x41, 0x28, 0xa0, 0x0d, 0x01, 0x31, 0x41, 0x28, 0xa2, 0x09, 0x42,
  0x21, 0x6d, 0x58, 0x88, 0xce, 0xfb, 0xc0, 0x20, 0x0c, 0x86, 0x30, 0x20,
  0xc4, 0x00, 0x20, 0x42, 0x55, 0x84, 0x35, 0xf4, 0xf4, 0x24, 0x45, 0x34,
  0x41, 0x28, 0xa6, 0x09, 0x02, 0xd1, 0x6c, 0x10, 0xcc, 0xc0, 0x0c, 0x36,
  0x2c, 0x03, 0x19, 0x78, 0x62, 0x00, 0x06, 0x65, 0x30, 0x94, 0xc1, 0x20,
  0x06, 0x67, 0xb0, 0x41, 0x18, 0x03, 0x34, 0x60, 0x32, 0x65, 0xf5, 0x45,
  0x15, 0x26, 0x77, 0x56, 0x46, 0x37, 0x41, 0x28, 0xa8, 0x09, 0x02, 0xe1,
  0x6c, 0x10, 0xcc, 0x80, 0x0d, 0x36, 0x2c, 0x84, 0x1a, 0x78, 0x6b, 0x00,
  0x06, 0x62, 0x30, 0x84, 0x01, 0x21, 0x06, 0x6d, 0xb0, 0x21, 0x70, 0x83,
  0x0d, 0x43, 0x1a, 0xbc, 0x01, 0xb0, 0xa1, 0xd8, 0x38, 0x38, 0xc0, 0x80,
  0x2a, 0x6c, 0x6c, 0x76, 0x6d, 0x2e, 0x69, 0x64, 0x65, 0x6e, 0x74, 0x53,
  0x82, 0xa0, 0x0a, 0x19, 0x9e, 0x8b, 0x5d, 0x99, 0xdc, 0x5c, 0xda, 0x9b,
  0xdb, 0x94, 0x80, 0x68, 0x42, 0x86, 0xe7, 0x62, 0x17, 0xc6, 0x66, 0x57,
  0x26, 0x37, 0x25, 0x30, 0xea, 0x90, 0xe1, 0xb9, 0xcc, 0xa1, 0x85, 0x91,
  0x95, 0xc9, 0x35, 0xbd, 0x91, 0x95, 0xb1, 0x4d, 0x09, 0x90, 0x32, 0x64,
  0x78, 0x2e, 0x72, 0x65, 0x73, 0x6f, 0x75, 0x72, 0x63, 0x65, 0x73, 0x53,
  0x82, 0xab, 0x0e, 0x19, 0x9e, 0x8b, 0x5d, 0x5a, 0xd9, 0x5d, 0x12, 0xd9,
  0x14, 0x5d, 0x18, 0x5d, 0xd9, 0x94, 0x20, 0xab, 0x43, 0x86, 0xe7, 0x52,
  0xe6, 0x46, 0x27, 0x97, 0x07, 0xf5, 0x96, 0xe6, 0x46, 0x37, 0x37, 0x25,
  0x80, 0x03, 0x00, 0x79, 0x18, 0x00, 0x00, 0x4c, 0x00, 0x00, 0x00, 0x33,
  0x08, 0x80, 0x1c, 0xc4, 0xe1, 0x1c, 0x66, 0x14, 0x01, 0x3d, 0x88, 0x43,
  0x38, 0x84, 0xc3, 0x8c, 0x42, 0x80, 0x07, 0x79, 0x78, 0x07, 0x73, 0x98,
  0x71, 0x0c, 0xe6, 0x00, 0x0f, 0xed, 0x10, 0x0e, 0xf4, 0x80, 0x0e, 0x33,
  0x0c, 0x42, 0x1e, 0xc2, 0xc1, 0x1d, 0xce, 0xa1, 0x1c, 0x66, 0x30, 0x05,
  0x3d, 0x88, 0x43, 0x38, 0x84, 0x83, 0x1b, 0xcc, 0x03, 0x3d, 0xc8, 0x43,
  0x3d, 0x8c, 0x03, 0x3d, 0xcc, 0x78, 0x8c, 0x74, 0x70, 0x07, 0x7b, 0x08,
  0x07, 0x79, 0x48, 0x87, 0x70, 0x70, 0x07, 0x7a, 0x70, 0x03, 0x76, 0x78,
  0x87, 0x70, 0x20, 0x87, 0x19, 0xcc, 0x11, 0x0e, 0xec, 0x90, 0x0e, 0xe1,
  0x30, 0x0f, 0x6e, 0x30, 0x0f, 0xe3, 0xf0, 0x0e, 0xf0, 0x50, 0x0e, 0x33,
  0x10, 0xc4, 0x1d, 0xde, 0x21, 0x1c, 0xd8, 0x21, 0x1d, 0xc2, 0x61, 0x1e,
  0x66, 0x30, 0x89, 0x3b, 0xbc, 0x83, 0x3b, 0xd0, 0x43, 0x39, 0xb4, 0x03,
  0x3c, 0xbc, 0x83, 0x3c, 0x84, 0x03, 0x3b, 0xcc, 0xf0, 0x14, 0x76, 0x60,
  0x07, 0x7b, 0x68, 0x07, 0x37, 0x68, 0x87, 0x72, 0x68, 0x07, 0x37, 0x80,
  0x87, 0x70, 0x90, 0x87, 0x70, 0x60, 0x07, 0x76, 0x28, 0x07, 0x76, 0xf8,
  0x05, 0x76, 0x78, 0x87, 0x77, 0x80, 0x87, 0x5f, 0x08, 0x87, 0x71, 0x18,
  0x87, 0x72, 0x98, 0x87, 0x79, 0x98, 0x81, 0x2c, 0xee, 0xf0, 0x0e, 0xee,
  0xe0, 0x0e, 0xf5, 0xc0, 0x0e, 0xec, 0x30, 0x03, 0x62, 0xc8, 0xa1, 0x1c,
  0xe4, 0xa1, 0x1c, 0xcc, 0xa1, 0x1c, 0xe4, 0xa1, 0x1c, 0xdc, 0x61, 0x1c,
  0xca, 0x21, 0x1c, 0xc4, 0x81, 0x1d, 0xca, 0x61, 0x06, 0xd6, 0x90, 0x43,
  0x39, 0xc8, 0x43, 0x39, 0x98, 0x43, 0x39, 0xc8, 0x43, 0x39, 0xb8, 0xc3,
  0x38, 0x94, 0x43, 0x38, 0x88, 0x03, 0x3b, 0x94, 0xc3, 0x2f, 0xbc, 0x83,
  0x3c, 0xfc, 0x82, 0x3b, 0xd4, 0x03, 0x3b, 0xb0, 0xc3, 0x0c, 0xc4, 0x21,
  0x07, 0x7c, 0x70, 0x03, 0x7a, 0x28, 0x87, 0x76, 0x80, 0x87, 0x19, 0xd1,
  0x43, 0x0e, 0xf8, 0xe0, 0x06, 0xe4, 0x20, 0x0e, 0xe7, 0xe0, 0x06, 0xf6,
  0x10, 0x0e, 0xf2, 0xc0, 0x0e, 0xe1, 0x90, 0x0f, 0xef, 0x50, 0x0f, 0xf4,
  0x00, 0x00, 0x00, 0x71, 0x20, 0x00, 0x00, 0x1d, 0x00, 0x00, 0x00, 0x06,
  0xe0, 0xa4, 0xec, 0xb6, 0x38, 0x0e, 0xe3, 0x5d, 0x53, 0x04, 0x08, 0x93,
  0x15, 0x6c, 0xc3, 0xe5, 0x3b, 0x8f, 0x2f, 0x04, 0x54, 0x51, 0x10, 0x51,
  0xe9, 0x00, 0x43, 0x49, 0x18, 0x80, 0x80, 0xf9, 0xc5, 0x6d, 0x9b, 0x81,
  0x34, 0x5c, 0xbe, 0xf3, 0xf8, 0x42, 0x44, 0x00, 0x13, 0x11, 0x02, 0xcd,
  0xb0, 0x10, 0x16, 0x30, 0x0d, 0x97, 0xef, 0x3c, 0xfe, 0xe2, 0x00, 0x83,
  0xd8, 0x3c, 0xd4, 0xe4, 0x17, 0xb7, 0x6d, 0x03, 0xd0, 0x70, 0xf9, 0xce,
  0xe3, 0x4b, 0x00, 0xf3, 0x2c, 0x84, 0x5f, 0xdc, 0xb6, 0x09, 0x54, 0xc3,
  0xe5, 0x3b, 0x8f, 0x2f, 0x4d, 0x4e, 0x44, 0xa0, 0xd4, 0xf4, 0x50, 0x93,
  0x5f, 0xdc, 0xb6, 0x11, 0x3c, 0xc3, 0xe5, 0x3b, 0x8f, 0x4f, 0x35, 0x40,
  0x84, 0xf9, 0xc5, 0x6d, 0x03, 0x00, 0x00, 0x61, 0x20, 0x00, 0x00, 0x4f,
  0x00, 0x00, 0x00, 0x13, 0x04, 0x41, 0x2c, 0x10, 0x00, 0x00, 0x00, 0x08,
  0x00, 0x00, 0x00, 0x44, 0x8d, 0x00, 0x50, 0x51, 0x02, 0x44, 0x94, 0x43,
  0x29, 0x94, 0xdc, 0x0c, 0x40, 0x21, 0x14, 0x5e, 0xd9, 0x15, 0x08, 0x0d,
  0x33, 0x00, 0x63, 0x04, 0x20, 0x08, 0x82, 0xf8, 0x07, 0x00, 0x00, 0x23,
  0x06, 0x09, 0x00, 0x82, 0x60, 0x50, 0x7d, 0xc8, 0xd4, 0x75, 0xcc, 0x88,
  0x41, 0x02, 0x80, 0x20, 0x18, 0x54, 0x60, 0x90, 0x58, 0x9e, 0xd7, 0x8c,
  0x18, 0x24, 0x00, 0x08, 0x82, 0x41, 0x15, 0x06, 0x0a, 0xf5, 0x7d, 0xce,
  0x88, 0x41, 0x02, 0x80, 0x20, 0x18, 0x18, 0x67, 0x90, 0x84, 0x01, 0x18,
  0x58, 0xca, 0x88, 0x41, 0x02, 0x80, 0x20, 0x18, 0x18, 0x68, 0xa0, 0x88,
  0x41, 0x18, 0x3c, 0xcb, 0x88, 0xc1, 0x03, 0x80, 0x20, 0x18, 0x34, 0x67,
  0xa0, 0x14, 0x84, 0x10, 0x1c, 0x87, 0x18, 0x88, 0x01, 0x73, 0x8c, 0x26,
  0x04, 0xc0, 0x68, 0x82, 0x10, 0x8c, 0x26, 0x0c, 0xc2, 0x68, 0x02, 0x31,
  0x8c, 0x18, 0x1c, 0x00, 0x08, 0x82, 0x81, 0xa4, 0x06, 0x0e, 0xd2, 0x8c,
  0x26, 0x04, 0xc0, 0x68, 0x82, 0x10, 0x8c, 0x26, 0x0c, 0xc2, 0x68, 0x02,
  0x31, 0x58, 0x42, 0xc4, 0xc7, 0x12, 0x22, 0x3e, 0x96, 0x10, 0xf1, 0xb1,
  0x84, 0x88, 0x8f, 0x51, 0x48, 0x7c, 0xac, 0x42, 0xe2, 0x63, 0x16, 0x12,
  0x1f, 0xbb, 0x90, 0xf8, 0x18, 0x42, 0xd0, 0xc7, 0x10, 0x82, 0x3e, 0x86,
  0x10, 0xf4, 0x31, 0x84, 0xa0, 0xcf, 0x88, 0x81, 0x01, 0x80, 0x20, 0x18,
  0x3c, 0x7c, 0x50, 0x06, 0xc4, 0x88, 0x81, 0x01, 0x80, 0x20, 0x18, 0x3c,
  0x7d, 0x60, 0x06, 0xc4, 0x88, 0x81, 0x01, 0x80, 0x20, 0x18, 0x3c, 0x7e,
  0x70, 0x06, 0xc4, 0x88, 0x81, 0x01, 0x80, 0x20, 0x18, 0x3c, 0x7f, 0x80,
  0x06, 0xc4, 0x88, 0x41, 0x02, 0x80, 0x20, 0x18, 0x20, 0xa2, 0x80, 0x06,
  0x7c, 0xc0, 0x07, 0x72, 0x40, 0x8c, 0x18, 0x24, 0x00, 0x08, 0x82, 0x01,
  0x22, 0x0a, 0x68, 0xc0, 0x07, 0x7c, 0xa0, 0x06, 0xc3, 0x88, 0x41, 0x02,
  0x80, 0x20, 0x18, 0x20, 0xa2, 0x80, 0x06, 0x7c, 0xc0, 0x07, 0x71, 0x20,
  0x8c, 0x18, 0x24, 0x00, 0x08, 0x82, 0x01, 0x22, 0x0a, 0x68, 0xc0, 0x07,
  0x7c, 0x40, 0x07, 0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
