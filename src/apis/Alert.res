type options = {
  cancelable?: bool,
  onDismiss?: unit => unit,
}

@obj // @deprecated("Directly create record instead")
external options: (~cancelable: bool=?, ~onDismiss: unit => unit=?, unit) => options = ""

type style = [#default | #cancel | #destructive]

type button = {
  text?: string,
  onPress?: unit => unit,
  style?: style,
}

@obj // @deprecated("Directly create record instead")
external button: (~text: string=?, ~onPress: unit => unit=?, ~style: style=?, unit) => button = ""

@scope("Alert") @module("react-native")
external alert: (
  ~title: string,
  ~message: string=?,
  ~buttons: array<button>=?,
  ~options: options=?,
  unit,
) => unit = "alert"

type type_ = [
  | #default
  | #"plain-text"
  | #"secure-text"
  | #"login-password"
]

@scope("Alert") @module("react-native")
external prompt: (
  ~title: string,
  ~message: string=?,
  ~callbackOrButtons: @unwrap
  [
    | #callback(string => unit)
    | #buttons(array<button>)
  ]=?,
  ~type_: type_=?,
  ~defaultValue: string=?,
  ~keyboardType: string=?,
  unit,
) => unit = "prompt"
