include ScrollViewElement

type contentOffset = {x: float, y: float}
@deprecated("Directly create record instead") @obj
external contentOffset: (~x: float, ~y: float) => contentOffset = ""

type contentInsetAdjustmentBehavior = [
  | #automatic
  | #scrollableAxes
  | #never
  | #always
]

type decelerationRate = [#fast | #normal]

type indicatorStyle = [#default | #black | #white]

type keyboardDismissMode = [
  | #none
  | #interactive
  | #"on-drag"
]

type keyboardShouldPersistTaps = [#always | #never | #handled]

type overScrollMode = [#always | #never | #auto]

type snapToAlignment = [#start | #center | #end]

type maintainVisibleContentPosition = {
  autoscrollToTopThreshold?: float,
  minIndexForVisible: int,
}

type scrollViewProps = {
  ...View.viewProps,
  alwaysBounceHorizontal?: bool,
  alwaysBounceVertical?: bool,
  automaticallyAdjustContentInsets?: bool,
  bounces?: bool,
  bouncesZoom?: bool,
  canCancelContentTouches?: bool,
  centerContent?: bool,
  contentContainerStyle?: Style.t,
  contentInset?: Rect.t,
  contentInsetAdjustmentBehavior?: contentInsetAdjustmentBehavior,
  contentOffset?: contentOffset,
  decelerationRate?: decelerationRate,
  directionalLockEnabled?: bool,
  endFillColor?: Color.t,
  fadingEdgeLength?: float,
  horizontal?: bool,
  indicatorStyle?: indicatorStyle,
  keyboardDismissMode?: keyboardDismissMode,
  keyboardShouldPersistTaps?: keyboardShouldPersistTaps,
  maintainVisibleContentPosition?: maintainVisibleContentPosition,
  maximumZoomScale?: float,
  minimumZoomScale?: float,
  nestedScrollEnabled?: bool,
  onContentSizeChange?: ((float, float)) => unit,
  onMomentumScrollBegin?: Event.scrollEvent => unit,
  onMomentumScrollEnd?: Event.scrollEvent => unit,
  onScroll?: Event.scrollEvent => unit,
  onScrollBeginDrag?: Event.scrollEvent => unit,
  onScrollEndDrag?: Event.scrollEvent => unit,
  overScrollMode?: overScrollMode,
  pagingEnabled?: bool,
  pinchGestureEnabled?: bool,
  refreshControl?: React.element,
  scrollEnabled?: bool,
  scrollEventThrottle?: int,
  scrollIndicatorInsets?: Rect.t,
  scrollPerfTag?: string,
  scrollsToTop?: bool,
  scrollToOverflowEnabled?: bool,
  showsHorizontalScrollIndicator?: bool,
  showsVerticalScrollIndicator?: bool,
  snapToAlignment?: snapToAlignment,
  snapToEnd?: bool,
  snapToInterval?: float,
  snapToOffsets?: array<float>,
  snapToStart?: bool,
  stickyHeaderHiddenOnScroll?: bool,
  stickyHeaderIndices?: array<int>,
  zoomScale?: float,
}

type props = {
  ref?: ref,
  ...scrollViewProps,
}

@module("react-native")
external make: React.component<props> = "ScrollView"
