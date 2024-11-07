type content = {
  title?: string,
  message?: string,
  url?: string,
}

@deprecated("Directly create record instead") @obj
external content: (~title: string=?, ~message: string=?, ~url: string=?, unit) => content = ""

type options = {
  subject?: string,
  tintColor?: string,
  excludedActivityTypes?: array<string>,
  dialogTitle?: string,
  anchor?: int,
}

@deprecated("Directly create record instead") @obj
external options: (
  ~subject: string=?,
  ~tintColor: string=?,
  ~excludedActivityTypes: array<string>=?,
  ~dialogTitle: string=?,
  ~anchor: int=?,
  unit,
) => options = ""

type action

@module("react-native") @scope("Share")
external sharedAction: action = "sharedAction"

@module("react-native") @scope("Share")
external dismissedAction: action = "dismissedAction"

// This is usually only used as a callback param and not created by the user.
// Therefore prefer option<...> to an optional field for easier matching.
type shareResult = {
  action: action,
  activityType: option<string>,
}

// multiple externals
@module("react-native") @scope("Share")
external share: content => promise<shareResult> = "share"

// multiple externals
@module("react-native") @scope("Share")
external shareWithOptions: (content, options) => promise<bool> = "share"
