#if 0
;
; Input signature:
;
; Name                 Index   Mask Register SysValue  Format   Used
; -------------------- ----- ------ -------- -------- ------- ------
; TEXCOORD                 0   xy          0     NONE   float       
; TEXCOORD                 1   xyzw        1     NONE   float       
; TEXCOORD                 2   xyz         2     NONE   float   xyz 
; COLOR                    0   xyzw        3     NONE   float   xyzw
;
;
; Output signature:
;
; Name                 Index   Mask Register SysValue  Format   Used
; -------------------- ----- ------ -------- -------- ------- ------
; SV_Target                0   xyzw        0   TARGET   float   xyzw
;
; shader debug name: C:\Users\marcu\Downloads\DirectXTK12-main\DirectXTK12-main\Src/Shaders/Compiled\DebugEffect_PSHemiAmbient.pdb
; shader hash: fc1125976563a5f8d177117eb7964e17
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
; TEXCOORD                 0                 linear       
; TEXCOORD                 1                 linear       
; TEXCOORD                 2                 linear       
; COLOR                    0                 linear       
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
;   [208 x i8] (type annotation not present)
;
; }
;
;
; Resource Bindings:
;
; Name                                 Type  Format         Dim      ID      HLSL Bind  Count
; ------------------------------ ---------- ------- ----------- ------- -------------- ------
;                                   cbuffer      NA          NA     CB0            cb0     1
;
;
; ViewId state:
;
; Number of inputs: 16, outputs: 4
; Outputs dependent on ViewId: {  }
; Inputs contributing to computation of Outputs:
;   output 0 depends on inputs: { 8, 9, 10, 12 }
;   output 1 depends on inputs: { 8, 9, 10, 13 }
;   output 2 depends on inputs: { 8, 9, 10, 14 }
;   output 3 depends on inputs: { 15 }
;
target datalayout = "e-m:e-p:32:32-i1:32-i8:32-i16:32-i32:32-i64:64-f16:32-f32:32-f64:64-n8:16:32:64"
target triple = "dxil-ms-dx"

%dx.types.Handle = type { i8* }
%dx.types.CBufRet.f32 = type { float, float, float, float }
%hostlayout.Parameters = type { <3 x float>, float, <3 x float>, [4 x <4 x float>], [3 x <3 x float>], [4 x <4 x float>] }

define void @PSHemiAmbient() {
  %1 = call %dx.types.Handle @dx.op.createHandle(i32 57, i8 2, i32 0, i32 0, i1 false)  ; CreateHandle(resourceClass,rangeId,index,nonUniformIndex)
  %2 = call float @dx.op.loadInput.f32(i32 4, i32 3, i32 0, i8 0, i32 undef)  ; LoadInput(inputSigId,rowIndex,colIndex,gsVertexAxis)
  %3 = call float @dx.op.loadInput.f32(i32 4, i32 3, i32 0, i8 1, i32 undef)  ; LoadInput(inputSigId,rowIndex,colIndex,gsVertexAxis)
  %4 = call float @dx.op.loadInput.f32(i32 4, i32 3, i32 0, i8 2, i32 undef)  ; LoadInput(inputSigId,rowIndex,colIndex,gsVertexAxis)
  %5 = call float @dx.op.loadInput.f32(i32 4, i32 3, i32 0, i8 3, i32 undef)  ; LoadInput(inputSigId,rowIndex,colIndex,gsVertexAxis)
  %6 = call float @dx.op.loadInput.f32(i32 4, i32 2, i32 0, i8 0, i32 undef)  ; LoadInput(inputSigId,rowIndex,colIndex,gsVertexAxis)
  %7 = call float @dx.op.loadInput.f32(i32 4, i32 2, i32 0, i8 1, i32 undef)  ; LoadInput(inputSigId,rowIndex,colIndex,gsVertexAxis)
  %8 = call float @dx.op.loadInput.f32(i32 4, i32 2, i32 0, i8 2, i32 undef)  ; LoadInput(inputSigId,rowIndex,colIndex,gsVertexAxis)
  %9 = call float @dx.op.dot3.f32(i32 55, float %6, float %7, float %8, float %6, float %7, float %8)  ; Dot3(ax,ay,az,bx,by,bz)
  %10 = call float @dx.op.unary.f32(i32 25, float %9)  ; Rsqrt(value)
  %11 = fmul fast float %7, 5.000000e-01
  %12 = fmul fast float %11, %10
  %13 = fadd fast float %12, 5.000000e-01
  %14 = call %dx.types.CBufRet.f32 @dx.op.cbufferLoadLegacy.f32(i32 59, %dx.types.Handle %1, i32 0)  ; CBufferLoadLegacy(handle,regIndex)
  %15 = extractvalue %dx.types.CBufRet.f32 %14, 0
  %16 = extractvalue %dx.types.CBufRet.f32 %14, 1
  %17 = extractvalue %dx.types.CBufRet.f32 %14, 2
  %18 = call %dx.types.CBufRet.f32 @dx.op.cbufferLoadLegacy.f32(i32 59, %dx.types.Handle %1, i32 1)  ; CBufferLoadLegacy(handle,regIndex)
  %19 = extractvalue %dx.types.CBufRet.f32 %18, 0
  %20 = extractvalue %dx.types.CBufRet.f32 %18, 1
  %21 = extractvalue %dx.types.CBufRet.f32 %18, 2
  %22 = fmul fast float %13, %19
  %23 = fmul fast float %13, %20
  %24 = fmul fast float %13, %21
  %25 = fadd fast float %22, %15
  %26 = fadd fast float %23, %16
  %27 = fadd fast float %24, %17
  %28 = fmul fast float %25, %2
  %29 = fmul fast float %26, %3
  %30 = fmul fast float %27, %4
  call void @dx.op.storeOutput.f32(i32 5, i32 0, i32 0, i8 0, float %28)  ; StoreOutput(outputSigId,rowIndex,colIndex,value)
  call void @dx.op.storeOutput.f32(i32 5, i32 0, i32 0, i8 1, float %29)  ; StoreOutput(outputSigId,rowIndex,colIndex,value)
  call void @dx.op.storeOutput.f32(i32 5, i32 0, i32 0, i8 2, float %30)  ; StoreOutput(outputSigId,rowIndex,colIndex,value)
  call void @dx.op.storeOutput.f32(i32 5, i32 0, i32 0, i8 3, float %5)  ; StoreOutput(outputSigId,rowIndex,colIndex,value)
  ret void
}

; Function Attrs: nounwind readnone
declare float @dx.op.loadInput.f32(i32, i32, i32, i8, i32) #0

; Function Attrs: nounwind
declare void @dx.op.storeOutput.f32(i32, i32, i32, i8, float) #1

; Function Attrs: nounwind readnone
declare float @dx.op.dot3.f32(i32, float, float, float, float, float, float) #0

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
!dx.viewIdState = !{!7}
!dx.entryPoints = !{!8}

!0 = !{!"clang version 3.7 (tags/RELEASE_370/final)"}
!1 = !{i32 1, i32 0}
!2 = !{i32 1, i32 6}
!3 = !{!"ps", i32 6, i32 0}
!4 = !{null, null, !5, null}
!5 = !{!6}
!6 = !{i32 0, %hostlayout.Parameters* undef, !"", i32 0, i32 0, i32 1, i32 208, null}
!7 = !{[18 x i32] [i32 16, i32 4, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 7, i32 7, i32 7, i32 0, i32 1, i32 2, i32 4, i32 8]}
!8 = !{void ()* @PSHemiAmbient, !"PSHemiAmbient", !9, !4, null}
!9 = !{!10, !20, null}
!10 = !{!11, !13, !15, !18}
!11 = !{i32 0, !"TEXCOORD", i8 9, i8 0, !12, i8 2, i32 1, i8 2, i32 0, i8 0, null}
!12 = !{i32 0}
!13 = !{i32 1, !"TEXCOORD", i8 9, i8 0, !14, i8 2, i32 1, i8 4, i32 1, i8 0, null}
!14 = !{i32 1}
!15 = !{i32 2, !"TEXCOORD", i8 9, i8 0, !16, i8 2, i32 1, i8 3, i32 2, i8 0, !17}
!16 = !{i32 2}
!17 = !{i32 3, i32 7}
!18 = !{i32 3, !"COLOR", i8 9, i8 0, !12, i8 2, i32 1, i8 4, i32 3, i8 0, !19}
!19 = !{i32 3, i32 15}
!20 = !{!21}
!21 = !{i32 0, !"SV_Target", i8 9, i8 16, !12, i8 0, i32 1, i8 4, i32 0, i8 0, !19}

#endif

const unsigned char DebugEffect_PSHemiAmbient[] = {
  0x44, 0x58, 0x42, 0x43, 0xa4, 0xc5, 0xb6, 0x06, 0x98, 0x1f, 0xdb, 0xdc,
  0x94, 0xa8, 0x69, 0x90, 0xf6, 0x32, 0x52, 0xbb, 0x01, 0x00, 0x00, 0x00,
  0x4f, 0x0a, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00,
  0x50, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x3b, 0x01, 0x00, 0x00,
  0x63, 0x02, 0x00, 0x00, 0x9b, 0x02, 0x00, 0x00, 0x17, 0x03, 0x00, 0x00,
  0x33, 0x03, 0x00, 0x00, 0x53, 0x46, 0x49, 0x30, 0x08, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x49, 0x53, 0x47, 0x31,
  0xa9, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x91, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9a, 0x00, 0x00, 0x00,
  0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
  0x02, 0x00, 0x00, 0x00, 0x07, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0xa3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
  0x0f, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x54, 0x45, 0x58, 0x43,
  0x4f, 0x4f, 0x52, 0x44, 0x00, 0x54, 0x45, 0x58, 0x43, 0x4f, 0x4f, 0x52,
  0x44, 0x00, 0x54, 0x45, 0x58, 0x43, 0x4f, 0x4f, 0x52, 0x44, 0x00, 0x43,
  0x4f, 0x4c, 0x4f, 0x52, 0x00, 0x4f, 0x53, 0x47, 0x31, 0x32, 0x00, 0x00,
  0x00, 0x01, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00,
  0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x53, 0x56, 0x5f, 0x54, 0x61, 0x72, 0x67,
  0x65, 0x74, 0x00, 0x50, 0x53, 0x56, 0x30, 0x20, 0x01, 0x00, 0x00, 0x30,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff,
  0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x04, 0x01, 0x00, 0x04, 0x01,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x02,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x0d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x24,
  0x00, 0x00, 0x00, 0x00, 0x54, 0x45, 0x58, 0x43, 0x4f, 0x4f, 0x52, 0x44,
  0x00, 0x54, 0x45, 0x58, 0x43, 0x4f, 0x4f, 0x52, 0x44, 0x00, 0x54, 0x45,
  0x58, 0x43, 0x4f, 0x4f, 0x52, 0x44, 0x00, 0x43, 0x4f, 0x4c, 0x4f, 0x52,
  0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
  0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x01,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x42, 0x00, 0x03,
  0x02, 0x00, 0x00, 0x0a, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01,
  0x01, 0x44, 0x00, 0x03, 0x02, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00, 0x02,
  0x00, 0x00, 0x00, 0x01, 0x02, 0x43, 0x00, 0x03, 0x02, 0x00, 0x00, 0x1c,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x44, 0x00, 0x03,
  0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
  0x00, 0x44, 0x10, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x07,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02,
  0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x52,
  0x54, 0x53, 0x30, 0x30, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01,
  0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30,
  0x00, 0x00, 0x00, 0x1d, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x49, 0x4c, 0x44, 0x4e, 0x74,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x00, 0x43, 0x3a, 0x5c, 0x55, 0x73,
  0x65, 0x72, 0x73, 0x5c, 0x6d, 0x61, 0x72, 0x63, 0x75, 0x5c, 0x44, 0x6f,
  0x77, 0x6e, 0x6c, 0x6f, 0x61, 0x64, 0x73, 0x5c, 0x44, 0x69, 0x72, 0x65,
  0x63, 0x74, 0x58, 0x54, 0x4b, 0x31, 0x32, 0x2d, 0x6d, 0x61, 0x69, 0x6e,
  0x5c, 0x44, 0x69, 0x72, 0x65, 0x63, 0x74, 0x58, 0x54, 0x4b, 0x31, 0x32,
  0x2d, 0x6d, 0x61, 0x69, 0x6e, 0x5c, 0x53, 0x72, 0x63, 0x2f, 0x53, 0x68,
  0x61, 0x64, 0x65, 0x72, 0x73, 0x2f, 0x43, 0x6f, 0x6d, 0x70, 0x69, 0x6c,
  0x65, 0x64, 0x5c, 0x44, 0x65, 0x62, 0x75, 0x67, 0x45, 0x66, 0x66, 0x65,
  0x63, 0x74, 0x5f, 0x50, 0x53, 0x48, 0x65, 0x6d, 0x69, 0x41, 0x6d, 0x62,
  0x69, 0x65, 0x6e, 0x74, 0x2e, 0x70, 0x64, 0x62, 0x00, 0x00, 0x00, 0x48,
  0x41, 0x53, 0x48, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc,
  0x11, 0x25, 0x97, 0x65, 0x63, 0xa5, 0xf8, 0xd1, 0x77, 0x11, 0x7e, 0xb7,
  0x96, 0x4e, 0x17, 0x44, 0x58, 0x49, 0x4c, 0x14, 0x07, 0x00, 0x00, 0x60,
  0x00, 0x00, 0x00, 0xc5, 0x01, 0x00, 0x00, 0x44, 0x58, 0x49, 0x4c, 0x00,
  0x01, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0xfc, 0x06, 0x00, 0x00, 0x42,
  0x43, 0xc0, 0xde, 0x21, 0x0c, 0x00, 0x00, 0xbc, 0x01, 0x00, 0x00, 0x0b,
  0x82, 0x20, 0x00, 0x02, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00, 0x07,
  0x81, 0x23, 0x91, 0x41, 0xc8, 0x04, 0x49, 0x06, 0x10, 0x32, 0x39, 0x92,
  0x01, 0x84, 0x0c, 0x25, 0x05, 0x08, 0x19, 0x1e, 0x04, 0x8b, 0x62, 0x80,
  0x14, 0x45, 0x02, 0x42, 0x92, 0x0b, 0x42, 0xa4, 0x10, 0x32, 0x14, 0x38,
  0x08, 0x18, 0x4b, 0x0a, 0x32, 0x52, 0x88, 0x48, 0x90, 0x14, 0x20, 0x43,
  0x46, 0x88, 0xa5, 0x00, 0x19, 0x32, 0x42, 0xe4, 0x48, 0x0e, 0x90, 0x91,
  0x22, 0xc4, 0x50, 0x41, 0x51, 0x81, 0x8c, 0xe1, 0x83, 0xe5, 0x8a, 0x04,
  0x29, 0x46, 0x06, 0x51, 0x18, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x1b,
  0x8c, 0xe0, 0xff, 0xff, 0xff, 0xff, 0x07, 0x40, 0x02, 0xa8, 0x0d, 0x84,
  0xf0, 0xff, 0xff, 0xff, 0xff, 0x03, 0x20, 0x6d, 0x30, 0x86, 0xff, 0xff,
  0xff, 0xff, 0x1f, 0x00, 0x09, 0xa8, 0x00, 0x49, 0x18, 0x00, 0x00, 0x03,
  0x00, 0x00, 0x00, 0x13, 0x82, 0x60, 0x42, 0x20, 0x4c, 0x08, 0x06, 0x00,
  0x00, 0x00, 0x00, 0x89, 0x20, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x32,
  0x22, 0x48, 0x09, 0x20, 0x64, 0x85, 0x04, 0x93, 0x22, 0xa4, 0x84, 0x04,
  0x93, 0x22, 0xe3, 0x84, 0xa1, 0x90, 0x14, 0x12, 0x4c, 0x8a, 0x8c, 0x0b,
  0x84, 0xa4, 0x4c, 0x10, 0x78, 0x23, 0x00, 0x25, 0x00, 0x14, 0x66, 0x00,
  0xe6, 0x08, 0xc0, 0x60, 0x8e, 0x00, 0x29, 0xc6, 0x20, 0x84, 0x14, 0x42,
  0xa6, 0x18, 0x80, 0x10, 0x52, 0x06, 0xa1, 0x82, 0x0c, 0x32, 0xc6, 0x18,
  0x63, 0x90, 0x2a, 0xc3, 0x20, 0x83, 0xd8, 0x51, 0xc3, 0xe5, 0x4f, 0xd8,
  0x43, 0x48, 0x3e, 0xb7, 0x51, 0xc5, 0x4a, 0x4c, 0x7e, 0x71, 0xdb, 0x88,
  0x18, 0x63, 0x0c, 0x2a, 0xf7, 0x0c, 0x97, 0x3f, 0x61, 0x0f, 0x21, 0xf9,
  0x21, 0xd0, 0x0c, 0x0b, 0x81, 0x82, 0x57, 0x08, 0x47, 0x20, 0xa1, 0x38,
  0x47, 0x10, 0x14, 0x03, 0x92, 0x42, 0xc8, 0x24, 0x3a, 0x10, 0x30, 0x8c,
  0x30, 0x0c, 0xc3, 0x08, 0xc4, 0x90, 0x04, 0x38, 0x07, 0xee, 0x55, 0x87,
  0x23, 0x4d, 0x0b, 0x80, 0x39, 0xd4, 0xe4, 0xa7, 0x40, 0x04, 0x30, 0xc4,
  0x44, 0x44, 0x12, 0x32, 0xee, 0xb8, 0x59, 0x67, 0xda, 0x29, 0x41, 0x00,
  0x00, 0x00, 0x00, 0x13, 0x14, 0x72, 0xc0, 0x87, 0x74, 0x60, 0x87, 0x36,
  0x68, 0x87, 0x79, 0x68, 0x03, 0x72, 0xc0, 0x87, 0x0d, 0xaf, 0x50, 0x0e,
  0x6d, 0xd0, 0x0e, 0x7a, 0x50, 0x0e, 0x6d, 0x00, 0x0f, 0x7a, 0x30, 0x07,
  0x72, 0xa0, 0x07, 0x73, 0x20, 0x07, 0x6d, 0x90, 0x0e, 0x71, 0xa0, 0x07,
  0x73, 0x20, 0x07, 0x6d, 0x90, 0x0e, 0x78, 0xa0, 0x07, 0x73, 0x20, 0x07,
  0x6d, 0x90, 0x0e, 0x71, 0x60, 0x07, 0x7a, 0x30, 0x07, 0x72, 0xd0, 0x06,
  0xe9, 0x30, 0x07, 0x72, 0xa0, 0x07, 0x73, 0x20, 0x07, 0x6d, 0x90, 0x0e,
  0x76, 0x40, 0x07, 0x7a, 0x60, 0x07, 0x74, 0xd0, 0x06, 0xe6, 0x10, 0x07,
  0x76, 0xa0, 0x07, 0x73, 0x20, 0x07, 0x6d, 0x60, 0x0e, 0x73, 0x20, 0x07,
  0x7a, 0x30, 0x07, 0x72, 0xd0, 0x06, 0xe6, 0x60, 0x07, 0x74, 0xa0, 0x07,
  0x76, 0x40, 0x07, 0x6d, 0xe0, 0x0e, 0x78, 0xa0, 0x07, 0x71, 0x60, 0x07,
  0x7a, 0x30, 0x07, 0x72, 0xa0, 0x07, 0x76, 0x40, 0x07, 0x43, 0x9e, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x86, 0x3c,
  0x06, 0x10, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c,
  0x79, 0x10, 0x20, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x18, 0xf2, 0x28, 0x40, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x30, 0xe4, 0x61, 0x80, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x60, 0xc8, 0x13, 0x01, 0x01, 0x30, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xc0, 0x90, 0x87, 0x02, 0x02, 0x60, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x80, 0x2c, 0x10, 0x10, 0x00, 0x00, 0x00, 0x32,
  0x1e, 0x98, 0x14, 0x19, 0x11, 0x4c, 0x90, 0x8c, 0x09, 0x26, 0x47, 0xc6,
  0x04, 0x43, 0x22, 0x25, 0x30, 0x02, 0x50, 0x0c, 0x05, 0x3a, 0x50, 0x04,
  0x65, 0x50, 0x0e, 0xe5, 0x41, 0xa5, 0x24, 0x46, 0x00, 0x8a, 0xa0, 0x10,
  0xca, 0xa0, 0x40, 0x88, 0xcf, 0x00, 0x50, 0x1f, 0x4b, 0x82, 0x08, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x80, 0xe3, 0x38, 0x80, 0x40, 0x20, 0x10, 0x00,
  0x00, 0x00, 0x00, 0x79, 0x18, 0x00, 0x00, 0x62, 0x00, 0x00, 0x00, 0x1a,
  0x03, 0x4c, 0x90, 0x46, 0x02, 0x13, 0x44, 0x35, 0x18, 0x63, 0x0b, 0x73,
  0x3b, 0x03, 0xb1, 0x2b, 0x93, 0x9b, 0x4b, 0x7b, 0x73, 0x03, 0x99, 0x71,
  0xb9, 0x01, 0x41, 0xa1, 0x0b, 0x3b, 0x9b, 0x7b, 0x91, 0x2a, 0x62, 0x2a,
  0x0a, 0x9a, 0x2a, 0xfa, 0x9a, 0xb9, 0x81, 0x79, 0x31, 0x4b, 0x73, 0x0b,
  0x63, 0x4b, 0xd9, 0x10, 0x04, 0x13, 0x04, 0xe2, 0x98, 0x20, 0x10, 0xc8,
  0x06, 0x61, 0x20, 0x26, 0x08, 0x44, 0xb2, 0x41, 0x18, 0x0c, 0x0a, 0x70,
  0x73, 0x1b, 0x06, 0xc4, 0x20, 0x26, 0x08, 0x5c, 0x45, 0x60, 0x82, 0x40,
  0x28, 0x1b, 0x10, 0x42, 0x59, 0x08, 0x62, 0x60, 0x80, 0x0d, 0x41, 0xb3,
  0x81, 0x00, 0x00, 0x07, 0x98, 0x20, 0x74, 0xd6, 0x86, 0x00, 0x9a, 0x20,
  0x08, 0x00, 0x1b, 0xa8, 0x29, 0xa4, 0xb2, 0xb6, 0xb4, 0xa0, 0x36, 0xb1,
  0xb4, 0x32, 0x37, 0x3a, 0x22, 0x54, 0x45, 0x58, 0x43, 0x4f, 0x4f, 0x52,
  0x44, 0x13, 0x84, 0xe2, 0x99, 0x20, 0x14, 0xd0, 0x86, 0x80, 0x98, 0x20,
  0x14, 0xd1, 0x86, 0x85, 0xa0, 0x2a, 0xeb, 0xc2, 0x06, 0x8c, 0xb0, 0x80,
  0x0d, 0xc1, 0x30, 0x41, 0x28, 0xa4, 0x0d, 0xcb, 0x40, 0x55, 0x96, 0x86,
  0x0d, 0xdb, 0x60, 0x01, 0x13, 0x04, 0x62, 0xd9, 0x10, 0x74, 0x13, 0x84,
  0x62, 0x9a, 0x20, 0x10, 0xcc, 0x04, 0x81, 0x68, 0x36, 0x08, 0x60, 0x10,
  0x06, 0x1b, 0x96, 0x8e, 0xaa, 0x2c, 0x0f, 0x1b, 0xbe, 0xce, 0x12, 0x03,
  0x16, 0x43, 0x4f, 0x4c, 0x4f, 0x52, 0x13, 0x04, 0xc2, 0xd9, 0x20, 0x80,
  0x41, 0x19, 0x6c, 0x58, 0xc0, 0x80, 0x0c, 0x2a, 0xeb, 0xc2, 0x86, 0x0d,
  0x0c, 0x2c, 0x33, 0xd8, 0x40, 0x64, 0xdc, 0x18, 0x9c, 0x01, 0x93, 0x29,
  0xab, 0x2f, 0xaa, 0x30, 0xb9, 0xb3, 0x32, 0xba, 0x09, 0x42, 0x41, 0x6d,
  0x58, 0x88, 0x34, 0xa8, 0xd4, 0xe0, 0xb2, 0x86, 0x8d, 0xb0, 0xcc, 0x60,
  0x43, 0xb0, 0x06, 0x1b, 0x06, 0x34, 0x60, 0x03, 0x60, 0x43, 0x21, 0x4d,
  0x6d, 0xf0, 0x00, 0x55, 0xd8, 0xd8, 0xec, 0xda, 0x5c, 0xd2, 0xc8, 0xca,
  0xdc, 0xe8, 0xa6, 0x04, 0x41, 0x15, 0x32, 0x3c, 0x17, 0xbb, 0x32, 0xb9,
  0xb9, 0xb4, 0x37, 0xb7, 0x29, 0x01, 0xd1, 0x84, 0x0c, 0xcf, 0xc5, 0x2e,
  0x8c, 0xcd, 0xae, 0x4c, 0x6e, 0x4a, 0x60, 0xd4, 0x21, 0xc3, 0x73, 0x99,
  0x43, 0x0b, 0x23, 0x2b, 0x93, 0x6b, 0x7a, 0x23, 0x2b, 0x63, 0x9b, 0x12,
  0x20, 0x65, 0xc8, 0xf0, 0x5c, 0xe4, 0xca, 0xe6, 0xde, 0xea, 0xe4, 0xc6,
  0xca, 0xe6, 0xa6, 0x04, 0x4e, 0x1d, 0x32, 0x3c, 0x17, 0xbb, 0xb4, 0xb2,
  0xbb, 0x24, 0xb2, 0x29, 0xba, 0x30, 0xba, 0xb2, 0x29, 0x01, 0x54, 0x87,
  0x0c, 0xcf, 0xa5, 0xcc, 0x8d, 0x4e, 0x2e, 0x0f, 0xea, 0x2d, 0xcd, 0x8d,
  0x6e, 0x6e, 0x4a, 0xd0, 0x06, 0x00, 0x00, 0x79, 0x18, 0x00, 0x00, 0x4c,
  0x00, 0x00, 0x00, 0x33, 0x08, 0x80, 0x1c, 0xc4, 0xe1, 0x1c, 0x66, 0x14,
  0x01, 0x3d, 0x88, 0x43, 0x38, 0x84, 0xc3, 0x8c, 0x42, 0x80, 0x07, 0x79,
  0x78, 0x07, 0x73, 0x98, 0x71, 0x0c, 0xe6, 0x00, 0x0f, 0xed, 0x10, 0x0e,
  0xf4, 0x80, 0x0e, 0x33, 0x0c, 0x42, 0x1e, 0xc2, 0xc1, 0x1d, 0xce, 0xa1,
  0x1c, 0x66, 0x30, 0x05, 0x3d, 0x88, 0x43, 0x38, 0x84, 0x83, 0x1b, 0xcc,
  0x03, 0x3d, 0xc8, 0x43, 0x3d, 0x8c, 0x03, 0x3d, 0xcc, 0x78, 0x8c, 0x74,
  0x70, 0x07, 0x7b, 0x08, 0x07, 0x79, 0x48, 0x87, 0x70, 0x70, 0x07, 0x7a,
  0x70, 0x03, 0x76, 0x78, 0x87, 0x70, 0x20, 0x87, 0x19, 0xcc, 0x11, 0x0e,
  0xec, 0x90, 0x0e, 0xe1, 0x30, 0x0f, 0x6e, 0x30, 0x0f, 0xe3, 0xf0, 0x0e,
  0xf0, 0x50, 0x0e, 0x33, 0x10, 0xc4, 0x1d, 0xde, 0x21, 0x1c, 0xd8, 0x21,
  0x1d, 0xc2, 0x61, 0x1e, 0x66, 0x30, 0x89, 0x3b, 0xbc, 0x83, 0x3b, 0xd0,
  0x43, 0x39, 0xb4, 0x03, 0x3c, 0xbc, 0x83, 0x3c, 0x84, 0x03, 0x3b, 0xcc,
  0xf0, 0x14, 0x76, 0x60, 0x07, 0x7b, 0x68, 0x07, 0x37, 0x68, 0x87, 0x72,
  0x68, 0x07, 0x37, 0x80, 0x87, 0x70, 0x90, 0x87, 0x70, 0x60, 0x07, 0x76,
  0x28, 0x07, 0x76, 0xf8, 0x05, 0x76, 0x78, 0x87, 0x77, 0x80, 0x87, 0x5f,
  0x08, 0x87, 0x71, 0x18, 0x87, 0x72, 0x98, 0x87, 0x79, 0x98, 0x81, 0x2c,
  0xee, 0xf0, 0x0e, 0xee, 0xe0, 0x0e, 0xf5, 0xc0, 0x0e, 0xec, 0x30, 0x03,
  0x62, 0xc8, 0xa1, 0x1c, 0xe4, 0xa1, 0x1c, 0xcc, 0xa1, 0x1c, 0xe4, 0xa1,
  0x1c, 0xdc, 0x61, 0x1c, 0xca, 0x21, 0x1c, 0xc4, 0x81, 0x1d, 0xca, 0x61,
  0x06, 0xd6, 0x90, 0x43, 0x39, 0xc8, 0x43, 0x39, 0x98, 0x43, 0x39, 0xc8,
  0x43, 0x39, 0xb8, 0xc3, 0x38, 0x94, 0x43, 0x38, 0x88, 0x03, 0x3b, 0x94,
  0xc3, 0x2f, 0xbc, 0x83, 0x3c, 0xfc, 0x82, 0x3b, 0xd4, 0x03, 0x3b, 0xb0,
  0xc3, 0x0c, 0xc4, 0x21, 0x07, 0x7c, 0x70, 0x03, 0x7a, 0x28, 0x87, 0x76,
  0x80, 0x87, 0x19, 0xd1, 0x43, 0x0e, 0xf8, 0xe0, 0x06, 0xe4, 0x20, 0x0e,
  0xe7, 0xe0, 0x06, 0xf6, 0x10, 0x0e, 0xf2, 0xc0, 0x0e, 0xe1, 0x90, 0x0f,
  0xef, 0x50, 0x0f, 0xf4, 0x00, 0x00, 0x00, 0x71, 0x20, 0x00, 0x00, 0x1c,
  0x00, 0x00, 0x00, 0x06, 0xd0, 0xa4, 0x6c, 0x48, 0x30, 0x88, 0xc6, 0x04,
  0x08, 0xd1, 0x4c, 0x56, 0xb0, 0x0d, 0x97, 0xef, 0x3c, 0xbe, 0x10, 0x50,
  0x45, 0x41, 0x44, 0xa5, 0x03, 0x0c, 0x25, 0x61, 0x00, 0x02, 0xe6, 0x17,
  0xb7, 0x6d, 0x06, 0xd2, 0x70, 0xf9, 0xce, 0xe3, 0x0b, 0x11, 0x01, 0x4c,
  0x44, 0x08, 0x34, 0xc3, 0x42, 0xd8, 0x80, 0x33, 0x5c, 0xbe, 0xf3, 0xf8,
  0x83, 0x33, 0xdd, 0x7e, 0x71, 0xdb, 0x16, 0x30, 0x0d, 0x97, 0xef, 0x3c,
  0xfe, 0xe2, 0x00, 0x83, 0xd8, 0x3c, 0xd4, 0xe4, 0x17, 0xb7, 0x6d, 0x02,
  0xd5, 0x70, 0xf9, 0xce, 0xe3, 0x4b, 0x93, 0x13, 0x11, 0x28, 0x35, 0x3d,
  0xd4, 0xe4, 0x17, 0xb7, 0x6d, 0x04, 0xcf, 0x70, 0xf9, 0xce, 0xe3, 0x53,
  0x0d, 0x10, 0x61, 0x7e, 0x71, 0xdb, 0x00, 0x61, 0x20, 0x00, 0x00, 0x4f,
  0x00, 0x00, 0x00, 0x13, 0x04, 0x41, 0x2c, 0x10, 0x00, 0x00, 0x00, 0x07,
  0x00, 0x00, 0x00, 0x34, 0x47, 0x00, 0x88, 0x14, 0xc2, 0x0c, 0x40, 0x29,
  0x94, 0x5d, 0xc9, 0x95, 0x5b, 0xc9, 0x50, 0x29, 0x01, 0x1a, 0x63, 0x04,
  0x20, 0x08, 0x82, 0xf0, 0x07, 0x00, 0x00, 0x23, 0x06, 0x09, 0x00, 0x82,
  0x60, 0x40, 0x6d, 0x05, 0x94, 0x65, 0xca, 0x88, 0x41, 0x02, 0x80, 0x20,
  0x18, 0x18, 0x61, 0xa0, 0x58, 0x9a, 0x94, 0x8c, 0x18, 0x24, 0x00, 0x08,
  0x82, 0x81, 0x21, 0x06, 0xcb, 0xb5, 0x11, 0xca, 0x88, 0x41, 0x02, 0x80,
  0x20, 0x18, 0x18, 0x63, 0xc0, 0x60, 0xdc, 0xb4, 0x8c, 0x18, 0x24, 0x00,
  0x08, 0x82, 0x81, 0x41, 0x06, 0x4d, 0xd6, 0x49, 0xcc, 0x88, 0x41, 0x02,
  0x80, 0x20, 0x18, 0x18, 0x65, 0xe0, 0x6c, 0x9e, 0xd5, 0x8c, 0x18, 0x24,
  0x00, 0x08, 0x82, 0x81, 0x61, 0x06, 0x0f, 0xf7, 0x21, 0xce, 0x88, 0x41,
  0x02, 0x80, 0x20, 0x18, 0x18, 0x67, 0x00, 0x75, 0x60, 0x70, 0x3d, 0x23,
  0x06, 0x0b, 0x00, 0x82, 0x60, 0xa0, 0x98, 0x01, 0x33, 0x08, 0xc1, 0x20,
  0x04, 0x23, 0x06, 0x06, 0x00, 0x82, 0x60, 0xc0, 0x98, 0x01, 0x13, 0x18,
  0xb1, 0xc8, 0xc7, 0x02, 0x41, 0x3e, 0x16, 0x34, 0xf0, 0x19, 0x31, 0x38,
  0x00, 0x10, 0x04, 0x83, 0x28, 0x0d, 0xa6, 0xc6, 0x0c, 0x46, 0x13, 0x02,
  0x60, 0x34, 0x41, 0x08, 0x46, 0x13, 0x06, 0x61, 0xc4, 0xe0, 0x00, 0x40,
  0x10, 0x0c, 0xa2, 0x36, 0xb8, 0xa2, 0x35, 0x18, 0x4d, 0x08, 0x80, 0xd1,
  0x04, 0x21, 0x18, 0x4d, 0x18, 0x04, 0x4b, 0x06, 0xf9, 0x98, 0x32, 0xc8,
  0xc7, 0x96, 0x41, 0x3e, 0x36, 0x28, 0xf0, 0xb1, 0x41, 0x81, 0x8f, 0x0d,
  0x0a, 0x7c, 0x6c, 0xd0, 0xe4, 0x63, 0x83, 0x26, 0x1f, 0x1b, 0x34, 0xf9,
  0x8c, 0x18, 0x24, 0x00, 0x08, 0x82, 0x01, 0xd2, 0x07, 0x65, 0x70, 0x07,
  0x77, 0xf0, 0x06, 0xc3, 0x88, 0x41, 0x02, 0x80, 0x20, 0x18, 0x20, 0x7d,
  0x50, 0x06, 0x77, 0x70, 0x07, 0x60, 0x20, 0x8c, 0x18, 0x24, 0x00, 0x08,
  0x82, 0x01, 0xd2, 0x07, 0x65, 0x70, 0x07, 0x77, 0xe0, 0x06, 0xc1, 0x88,
  0x41, 0x02, 0x80, 0x20, 0x18, 0x20, 0x7d, 0x50, 0x06, 0x77, 0x70, 0x07,
  0x6c, 0xa0, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
