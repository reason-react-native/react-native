module Animation = {
  type t
  type endResult = {finished: bool}
  type endCallback = endResult => unit
  @send
  external start: (t, ~endCallback: endCallback=?, unit) => unit = "start"

  @send external stop: t => unit = "stop"
  @send external reset: t => unit = "reset"
}

module type Value = {
  type t
  type rawValue
  type addListenerCallback
}

type calculated

type regular

type value<'a>

module ValueAnimations = (Val: Value) => {
  module Decay = {
    type config = {
      velocity: Val.rawValue,
      useNativeDriver: bool,
      deceleration?: float,
      isInteraction?: bool,
      onComplete?: Animation.endCallback,
      iterations?: int,
    }

    @module("react-native") @scope("Animated")
    external decay: (Val.t, config) => Animation.t = "decay"
  }

  module Spring = {
    type toValue
    external fromRawValue: Val.rawValue => toValue = "%identity"
    external fromAnimatedValue: Val.t => toValue = "%identity"

    type config = {
      toValue: toValue,
      useNativeDriver: bool,
      restDisplacementThreshold?: float,
      overshootClamping?: bool,
      restSpeedThreshold?: float,
      velocity?: Val.rawValue,
      bounciness?: float,
      speed?: float,
      tension?: float,
      friction?: float,
      stiffness?: float,
      mass?: float,
      damping?: float,
      delay?: float,
      isInteraction?: bool,
      onComplete?: Animation.endCallback,
      iterations?: int,
    }

    @module("react-native") @scope("Animated")
    external spring: (Val.t, config) => Animation.t = "spring"
  }

  module Timing = {
    type toValue

    external fromRawValue: Val.rawValue => toValue = "%identity"
    external fromAnimatedValue: Val.t => toValue = "%identity"

    type config = {
      toValue: toValue,
      useNativeDriver: bool,
      easing?: Easing.t,
      duration?: float,
      delay?: float,
      isInteraction?: bool,
      onComplete?: Animation.endCallback,
      iterations?: int,
    }

    @module("react-native") @scope("Animated")
    external timing: (Val.t, config) => Animation.t = "timing"
  }
}

module Interpolation = {
  type t = value<calculated>
  type outputRange
  external fromStringArray: array<string> => outputRange = "%identity"
  external fromFloatArray: array<float> => outputRange = "%identity"

  type extrapolate = [#extend | #clamp | #identity]

  type config = {
    inputRange: array<float>,
    outputRange: outputRange,
    easing?: Easing.t,
    extrapolate?: extrapolate,
    extrapolateLeft?: extrapolate,
    extrapolateRight?: extrapolate,
  }

  @send external interpolate: (value<'a>, config) => t = "interpolate"
}

module ValueOperations = {
  @module("react-native") @scope("Animated")
  external add: (value<'a>, value<'b>) => value<calculated> = "add"
  @module("react-native") @scope("Animated")
  external divide: (value<'a>, value<'b>) => value<calculated> = "divide"
  @module("react-native") @scope("Animated")
  external multiply: (value<'a>, value<'b>) => value<calculated> = "multiply"
  @module("react-native") @scope("Animated")
  external modulo: (value<'a>, float) => value<calculated> = "modulo"
  @module("react-native") @scope("Animated")
  external subtract: (value<'a>, value<'b>) => value<calculated> = "subtract"
  @module("react-native") @scope("Animated")
  external diffClamp: (value<'a>, float, float) => value<calculated> = "diffClamp"
  let interpolate = Interpolation.interpolate
}

module ValueMethods = (Val: Value) => {
  type t = Val.t
  type rawValue = Val.rawValue
  type addListenerCallback = Val.addListenerCallback
  type callback = rawValue => unit

  @send external setValue: (t, rawValue) => unit = "setValue"
  @send external setOffset: (t, rawValue) => unit = "setOffset"
  @send external flattenOffset: t => unit = "flattenOffset"
  @send external extractOffset: t => unit = "extractOffset"
  @send
  external addListener: (t, addListenerCallback) => string = "addListener"
  @send external removeListener: (t, string) => unit = "removeListener"
  @send external removeAllListeners: t => unit = "removeAllListeners"

  @send
  external resetAnimation: (t, ~callback: callback=?, unit) => unit = "resetAnimation"

  @send
  external stopAnimation: (t, ~callback: callback=?, unit) => unit = "stopAnimation"

  include ValueAnimations(Val)
}

module Value = {
  include ValueMethods({
    type t = value<regular>
    type rawValue = float
    type addListenerCallback = {"value": rawValue} => unit
  })

  @new @scope("Animated") @module("react-native")
  external create: float => t = "Value"

  include ValueOperations
}

module ValueXY = {
  include ValueMethods({
    type t = {"x": Value.t, "y": Value.t}
    type rawValue = {"x": float, "y": float}
    type addListenerCallback = rawValue => unit
  })

  type layout = {
    left: Value.t,
    top: Value.t,
  }
  @new @scope("Animated") @module("react-native")
  external create: rawValue => t = "ValueXY"
  @send external getLayout: t => layout = "getLayout"
  @send
  external getTranslateTransform: t => array<Style.transform> = "getTranslateTransform"
}

module Color = {
  include ValueMethods({
    type t = {"r": Value.t, "g": Value.t, "b": Value.t, "a": Value.t}
    type rawValue = {"r": float, "g": float, "b": float, "a": float}
    type addListenerCallback = rawValue => unit
  })

  @obj external rgbaValue: (~r: float, ~g: float, ~b: float, ~a: float) => rawValue = ""

  @new @scope("Animated") @module("react-native")
  external create: rawValue => t = "Color"

  @new @scope("Animated") @module("react-native")
  external createFromString: Color.t => t = "Color"
}

@module("react-native") @scope("Animated")
external delay: float => Animation.t = "delay"

@module("react-native") @scope("Animated")
external sequence: array<Animation.t> => Animation.t = "sequence"

type parallelPayload = {stopTogether: bool}
@module("react-native") @scope("Animated")
external parallel: (array<Animation.t>, parallelPayload) => Animation.t = "parallel"

@module("react-native") @scope("Animated")
external stagger: (float, array<Animation.t>) => Animation.t = "stagger"

type loopConfig = {iterations?: int, resetBeforeIteration?: bool}
@deprecated("Directly create record instead") @obj
external loopConfig: (~iterations: int=?, ~resetBeforeIteration: bool=?) => loopConfig = ""

// multiple externals
@module("react-native") @scope("Animated")
external loop: Animation.t => Animation.t = "loop"

// multiple externals
@module("react-native") @scope("Animated")
external loopWithConfig: (Animation.t, loopConfig) => Animation.t = "loop"

type eventOptions<'a>
@obj
external eventOptions: (
  ~listener: 'a=?,
  ~useNativeDriver: bool,
  ~platformConfig: 'platformConfig=?,
  unit,
) => eventOptions<'a> = ""

// multiple externals
@module("react-native") @scope("Animated")
external event1: (array<'mapping>, eventOptions<'a>) => 'a = "event"

// multiple externals
@module("react-native") @scope("Animated")
external event2: (('mapping1, 'mapping2), eventOptions<'a>) => 'a = "event"

@module("react-native") @scope("Animated")
external createAnimatedComponent: React.component<'props> => React.component<'props> =
  "createAnimatedComponent"

let timing = Value.Timing.timing

let spring = Value.Spring.spring

let decay = Value.Decay.decay

let start = Animation.start

let stop = Animation.stop

let reset = Animation.reset

module StyleProp = {
  // methods to allow use of Animated values with Style props

  // these methods should not be used to get the current value

  // for angle, Color.t, and size expressed as percentage,
  // interpolated values are needed where the outputRange is
  // an appropriate array of strings

  external float: value<'a> => float = "%identity"
  external angle: value<calculated> => Style.angle = "%identity"
  external size: value<'a> => Style.size = "%identity"
  external margin: value<'a> => Style.margin = "%identity"
  external color: value<calculated> => Color.t = "%identity"

  // UNSAFE: allows to pass animated values everywhere,
  // use of more precise methods above is recommended
  external unsafeAny: value<'a> => 'b = "%identity"
}

module FlatList = {
  @react.component(: FlatList.props<'item, 'extraData>) @module("react-native") @scope("Animated")
  external make: FlatList.props<'item, 'extraData> => React.element = "FlatList"
}

module Image = {
  @react.component(: Image.props) @module("react-native") @scope("Animated")
  external make: Image.props => React.element = "Image"
}

module ScrollView = {
  @react.component(: ScrollView.props) @module("react-native") @scope("Animated")
  external make: ScrollView.props => React.element = "ScrollView"
}

module SectionList = {
  @react.component(: SectionList.props<'sectionData, 'item, 'extraData>)
  @module("react-native")
  @scope("Animated")
  external make: SectionList.props<'sectionData, 'item, 'extraData> => React.element = "SectionList"
}

module Text = {
  @react.component(: Text.props) @module("react-native") @scope("Animated")
  external make: Text.props => React.element = "Text"
}

module View = {
  @react.component(: View.props) @module("react-native") @scope("Animated")
  external make: View.props => React.element = "View"
}

type config = {useNativeDriver: bool}

@module("react-native")
external useAnimatedValue: (~initialValue: float, ~config: config=?, unit) => Value.t =
  "useAnimatedValue"
