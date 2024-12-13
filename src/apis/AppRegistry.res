type appKey = string
type section = string
type taskId = float
type taskKey = string

type task<'data> = 'data => promise<unit>
type taskProvider<'data> = unit => task<'data>
type taskCanceller = unit => unit
type taskCancelProvider = unit => taskCanceller

type componentProvider<'a> = unit => React.component<'a>
type wrapperComponentProvider<'a, 'b> = 'b => React.component<'a>

type appParameters

external asAppParameters: 'a => appParameters = "%identity"

type appConfig<'a> = {
  appKey: string,
  component?: componentProvider<'a>,
  run?: appParameters => unit,
  section?: bool,
}
@deprecated("Directly create record instead") @obj
external appConfig: (
  ~appKey: string,
  ~component: componentProvider<'a>=?,
  ~run: appParameters => unit=?,
  ~section: bool=?,
  unit,
) => appConfig<'a> = ""

type runnable<'a> = {
  "component": Js.Nullable.t<componentProvider<'a>>,
  @meth
  "run": appParameters => unit,
}

type registry<'a> = {
  sections: array<section>,
  runnables: dict<runnable<'a>>,
}

@module("react-native") @scope("AppRegistry")
external getAppKeys: unit => array<appKey> = "getAppKeys"

@module("react-native") @scope("AppRegistry")
external getRegistry: unit => registry<'a> = "getRegistry"

@module("react-native") @scope("AppRegistry")
external getRunnable: appKey => option<runnable<'a>> = "getRunnable"

@module("react-native") @scope("AppRegistry")
external getSectionKeys: unit => array<string> = "getSectionKeys"

@module("react-native") @scope("AppRegistry")
external getSections: unit => dict<runnable<'a>> = "getSections"

// multiple externals
@module("react-native") @scope("AppRegistry")
external registerComponent: (appKey, componentProvider<'a>) => unit = "registerComponent"

// multiple externals
@module("react-native") @scope("AppRegistry")
external registerComponentWithSection: (appKey, componentProvider<'a>, section) => unit =
  "registerComponent"

@module("react-native") @scope("AppRegistry")
external registerConfig: array<appConfig<'a>> => unit = "registerConfig"

@module("react-native") @scope("AppRegistry")
external registerRunnable: (appKey, appParameters => unit) => string = "registerRunnable"

@module("react-native") @scope("AppRegistry")
external registerSection: (appKey, componentProvider<'a>) => unit = "registerSection"

@module("react-native") @scope("AppRegistry")
external runApplication: (appKey, 'a) => unit = "runApplication"

@module("react-native") @scope("AppRegistry")
external setWrapperComponentProvider: wrapperComponentProvider<'a, 'b> => unit =
  "setWrapperComponentProvider"

@module("react-native") @scope("AppRegistry")
external unmountApplicationComponentAtRootTag: string => unit =
  "unmountApplicationComponentAtRootTag"

// Android only
@module("react-native") @scope("AppRegistry")
external cancelHeadlessTask: (taskId, taskKey) => unit = "cancelHeadlessTask"

@module("react-native") @scope("AppRegistry")
external registerCancellableHeadlessTask: (
  taskKey,
  taskProvider<'data>,
  taskCancelProvider,
) => unit = "registerCancellableHeadlessTask"

@module("react-native") @scope("AppRegistry")
external registerHeadlessTask: (taskKey, taskProvider<'data>) => unit = "registerHeadlessTask"

@module("react-native") @scope("AppRegistry")
external startHeadlessTask: (taskId, taskKey, 'data) => unit = "startHeadlessTask"

// react-native-web
type app = {"element": React.element, @meth "getStyleElement": unit => React.element}
@module("react-native") @scope("AppRegistry")
external getApplication: (string, {"initialProps": 'a}) => app = "getApplication"
