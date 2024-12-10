module Make = (
  T: {
    type t
  },
) => {
  type scrollToEndOptions = {animated?: bool, duration?: float}

  @deprecated("Directly create record instead") @obj
  external scrollToEndOptions: (~animated: bool=?, ~duration: float=?, unit) => scrollToEndOptions =
    ""

  // multiple externals
  @send external scrollToEnd: T.t => unit = "scrollToEnd"

  // multiple externals
  @send
  external scrollToEndWithOptions: (T.t, scrollToEndOptions) => unit = "scrollToEnd"

  @send
  external flashScrollIndicators: T.t => unit = "flashScrollIndicators"

  @send
  external setNativeProps: (T.t, {..}) => unit = "setNativeProps"
}
