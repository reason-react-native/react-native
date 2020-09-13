type t;

external array: array(t) => t = "%identity";
external arrayOption: array(option(t)) => t = "%identity";
/* list works too since RN accept recursive array of styles (ocaml list are recursive arrays in JS)*/
external list: list(t) => t = "%identity";
external listOption: list(option(t)) => t = "%identity";

// Escape hatch, in case something is added into RN but unsupported,
// Useful if you play with fancy platforms
// Use with caution
[@bs.val]
external unsafeAddStyle: ([@bs.as {json|{}|json}] _, t, Js.t('a)) => t =
  "Object.assign";

external unsafeStyle: Js.t('a) => t = "%identity";

type size = string;

external pt: float => size = "%identity";
external dp: float => size = "%identity";

let pct = num => num->Js.Float.toString ++ "%";

type margin = size;

[@bs.inline]
let auto = "auto";

type offset;
[@bs.obj] external offset: (~height: float, ~width: float) => offset;

type angle;
let deg: float => angle = num => (num->Js.Float.toString ++ "deg")->Obj.magic;
let rad: float => angle = num => (num->Js.Float.toString ++ "rad")->Obj.magic;

type transform;
[@bs.obj] external perspective: (~perspective: float) => transform;
[@bs.obj] external rotate: (~rotate: angle) => transform;
[@bs.obj] external rotateX: (~rotateX: angle) => transform;
[@bs.obj] external rotateY: (~rotateY: angle) => transform;
[@bs.obj] external rotateZ: (~rotateZ: angle) => transform;
[@bs.obj] external scale: (~scale: float) => transform;
[@bs.obj] external scaleX: (~scaleX: float) => transform;
[@bs.obj] external scaleY: (~scaleY: float) => transform;
[@bs.obj] external translateX: (~translateX: float) => transform;
[@bs.obj] external translateY: (~translateY: float) => transform;
[@bs.obj] external skewX: (~skewX: angle) => transform;
[@bs.obj] external skewY: (~skewY: angle) => transform;
// @todo matrix

external unsafeTransform: Js.t('a) => transform = "%identity";

type resizeMode = [ | `cover | `contain | `stretch | `repeat | `center];

type fontStyle = [ | `normal | `italic];

type textAlign = [ | `auto | `left | `right | `center | `justify];

type textAlignVertical = [ | `auto | `top | `bottom | `center];

type textDecorationStyle = [ | `solid | `double | `dotted | `dashed];

type textTransform = [ | `none | `uppercase | `lowercase | `capitalize];

type writingDirection = [ | `auto | `ltr | `rtl];

type backfaceVisibility = [ | `visible | `hidden];

type borderStyle = [ | `solid | `dotted | `dashed];

type display = [ | `none | `flex];

type overflow = [ | `visible | `hidden | `scroll];

type flexWrap = [ | `wrap | `nowrap];

type position = [ | `absolute | `relative];

// Styles are documented here
// https://github.com/facebook/react-native/blob/master/Libraries/StyleSheet/StyleSheetTypes.js

// Note that all border*Width are in layout styles & view styles too
// React Native JS codebase have those in View Styles Props again but with different types
// because layout styles props don't accept animated values.
// We don't do the distinction as ReasonML is an HMTS that doesn't support implicit subtyping

// ____DangerouslyImpreciseStyle_Internal
[@bs.obj]
// Dangerous Imprecise Style
// Contains all of
// - image style
// - text style
// - view style
// - transform style
// - shadow style
// - layout style
//
// *Comment below is supposed to be after the first ( below but refmt move it here*
// Image Style Props (https://reactnative.dev/docs/image-style-props)
external style:
  (
    ~resizeMode: resizeMode=?,
    ~overlayColor: Color.t=?,
    ~tintColor: Color.t=?,
    // Text Style Props (https://reactnative.dev/docs/text-style-props)
    ~color: Color.t=?,
    ~fontFamily: string=?,
    ~fontSize: float=?,
    ~fontStyle: fontStyle=?,
    ~fontVariant: array(FontVariant.t)=?,
    ~fontWeight: [@bs.string] [
                   | `normal
                   | `bold
                   | [@bs.as "100"] `_100
                   | [@bs.as "200"] `_200
                   | [@bs.as "300"] `_300
                   | [@bs.as "400"] `_400
                   | [@bs.as "500"] `_500
                   | [@bs.as "600"] `_600
                   | [@bs.as "700"] `_700
                   | [@bs.as "800"] `_800
                   | [@bs.as "900"] `_900
                 ]
                   =?,
    ~includeFontPadding: bool=?,
    ~letterSpacing: float=?,
    ~lineHeight: float=?,
    ~textAlign: textAlign=?,
    ~textAlignVertical: textAlignVertical=?,
    ~textDecorationColor: Color.t=?,
    ~textDecorationLine: [@bs.string] [
                           | `none
                           | `underline
                           | [@bs.as "line-through"] `lineThrough
                           | [@bs.as "underline line-through"]
                             `underlineLineThrough
                         ]
                           =?,
    ~textDecorationStyle: textDecorationStyle=?,
    ~textShadowColor: Color.t=?,
    ~textShadowOffset: offset=?,
    ~textShadowRadius: float=?,
    ~textTransform: textTransform=?,
    ~writingDirection: writingDirection=?,
    // View styles https://reactnative.dev/docs/view-style-props
    ~backfaceVisibility: backfaceVisibility=?,
    ~backgroundColor: Color.t=?,
    ~borderBottomColor: Color.t=?,
    ~borderBottomEndRadius: float=?,
    ~borderBottomLeftRadius: float=?,
    ~borderBottomRightRadius: float=?,
    ~borderBottomStartRadius: float=?,
    ~borderBottomWidth: float=?,
    ~borderColor: Color.t=?,
    ~borderEndColor: Color.t=?,
    ~borderEndWidth: float=?,
    ~borderLeftColor: Color.t=?,
    ~borderLeftWidth: float=?,
    ~borderRadius: float=?,
    ~borderRightColor: Color.t=?,
    ~borderRightWidth: float=?,
    ~borderStartColor: Color.t=?,
    ~borderStartWidth: float=?,
    ~borderStyle: borderStyle=?,
    ~borderTopColor: Color.t=?,
    ~borderTopEndRadius: float=?,
    ~borderTopLeftRadius: float=?,
    ~borderTopRightRadius: float=?,
    ~borderTopStartRadius: float=?,
    ~borderTopWidth: float=?,
    ~borderWidth: float=?,
    ~elevation: float=?,
    ~opacity: float=?,
    // Transform Props (https://reactnative.dev/docs/transforms#props)
    ~transform: array(transform)=?, // all other transform props are deprecated
    // Shadow Props (https://reactnative.dev/docs/shadow-props)
    ~shadowColor: Color.t=?,
    ~shadowOffset: offset=?,
    ~shadowOpacity: float=?,
    ~shadowRadius: float=?,
    // Layout Style Props (https://reactnative.dev/docs/layout-props)
    ~alignContent: [@bs.string] [
                     | [@bs.as "flex-start"] `flexStart
                     | [@bs.as "flex-end"] `flexEnd
                     | `center
                     | `stretch
                     | [@bs.as "space-around"] `spaceAround
                     | [@bs.as "space-between"] `spaceBetween
                   ]
                     =?,
    ~alignItems: [@bs.string] [
                   | [@bs.as "flex-start"] `flexStart
                   | [@bs.as "flex-end"] `flexEnd
                   | `center
                   | `stretch
                   | `baseline
                 ]
                   =?,
    ~alignSelf: [@bs.string] [
                  | `auto
                  | [@bs.as "flex-start"] `flexStart
                  | [@bs.as "flex-end"] `flexEnd
                  | `center
                  | `stretch
                  | `baseline
                ]
                  =?,
    ~aspectRatio: float=?,
    // border*Width are commented because already in view styles props (see explanation at the top)
    // ~borderBottomWidth: float=?,
    // ~borderEndWidth: float=?,
    // ~borderLeftWidth: float=?,
    // ~borderRightWidth: float=?,
    // ~borderStartWidth: float=?,
    // ~borderTopWidth: float=?,
    // ~borderWidth: float=?,
    ~bottom: size=?,
    ~direction: [@bs.string] [ | [@bs.as "inherit"] `inherit_ | `ltr | `rtl]=?,
    ~display: display=?,
    ~_end: size=?,
    ~flex: float=?,
    ~flexBasis: margin=?,
    ~flexDirection: [@bs.string] [
                      | `row
                      | [@bs.as "row-reverse"] `rowReverse
                      | `column
                      | [@bs.as "column-reverse"] `columnReverse
                    ]
                      =?,
    ~flexGrow: float=?,
    ~flexShrink: float=?,
    ~flexWrap: flexWrap=?,
    ~height: size=?,
    ~justifyContent: [@bs.string] [
                       | [@bs.as "flex-start"] `flexStart
                       | [@bs.as "flex-end"] `flexEnd
                       | `center
                       | [@bs.as "space-around"] `spaceAround
                       | [@bs.as "space-between"] `spaceBetween
                       | [@bs.as "space-evenly"] `spaceEvenly
                     ]
                       =?,
    ~left: size=?,
    ~margin: margin=?,
    ~marginBottom: margin=?,
    ~marginEnd: margin=?,
    ~marginHorizontal: margin=?,
    ~marginLeft: margin=?,
    ~marginRight: margin=?,
    ~marginStart: margin=?,
    ~marginTop: margin=?,
    ~marginVertical: margin=?,
    ~maxHeight: size=?,
    ~maxWidth: size=?,
    ~minHeight: size=?,
    ~minWidth: size=?,
    ~overflow: overflow=?,
    ~padding: size=?,
    ~paddingBottom: size=?,
    ~paddingEnd: size=?,
    ~paddingHorizontal: size=?,
    ~paddingLeft: size=?,
    ~paddingRight: size=?,
    ~paddingStart: size=?,
    ~paddingTop: size=?,
    ~paddingVertical: size=?,
    ~position: position=?,
    ~right: size=?,
    ~start: size=?,
    ~top: size=?,
    ~width: size=?,
    ~zIndex: int=?,
    unit
  ) =>
  t;

// ____ViewStyleProp_Internal
[@bs.obj]
// *Comment below is supposed to be after the first ( below but refmt move it here*
// View styles https://reactnative.dev/docs/view-style-props
external viewStyle:
  (
    ~backfaceVisibility: backfaceVisibility=?,
    ~backgroundColor: Color.t=?,
    ~borderBottomColor: Color.t=?,
    ~borderBottomEndRadius: float=?,
    ~borderBottomLeftRadius: float=?,
    ~borderBottomRightRadius: float=?,
    ~borderBottomStartRadius: float=?,
    ~borderBottomWidth: float=?,
    ~borderColor: Color.t=?,
    ~borderEndColor: Color.t=?,
    ~borderEndWidth: float=?,
    ~borderLeftColor: Color.t=?,
    ~borderLeftWidth: float=?,
    ~borderRadius: float=?,
    ~borderRightColor: Color.t=?,
    ~borderRightWidth: float=?,
    ~borderStartColor: Color.t=?,
    ~borderStartWidth: float=?,
    ~borderStyle: borderStyle=?,
    ~borderTopColor: Color.t=?,
    ~borderTopEndRadius: float=?,
    ~borderTopLeftRadius: float=?,
    ~borderTopRightRadius: float=?,
    ~borderTopStartRadius: float=?,
    ~borderTopWidth: float=?,
    ~borderWidth: float=?,
    ~elevation: float=?,
    ~opacity: float=?,
    // Transform Props (https://reactnative.dev/docs/transforms#props)
    ~transform: array(transform)=?, // all other transform props are deprecated
    // Shadow Props (https://reactnative.dev/docs/shadow-props)
    ~shadowColor: Color.t=?,
    ~shadowOffset: offset=?,
    ~shadowOpacity: float=?,
    ~shadowRadius: float=?,
    // Layout Style Props (https://reactnative.dev/docs/layout-props)
    ~alignContent: [@bs.string] [
                     | [@bs.as "flex-start"] `flexStart
                     | [@bs.as "flex-end"] `flexEnd
                     | `center
                     | `stretch
                     | [@bs.as "space-around"] `spaceAround
                     | [@bs.as "space-between"] `spaceBetween
                   ]
                     =?,
    ~alignItems: [@bs.string] [
                   | [@bs.as "flex-start"] `flexStart
                   | [@bs.as "flex-end"] `flexEnd
                   | `center
                   | `stretch
                   | `baseline
                 ]
                   =?,
    ~alignSelf: [@bs.string] [
                  | `auto
                  | [@bs.as "flex-start"] `flexStart
                  | [@bs.as "flex-end"] `flexEnd
                  | `center
                  | `stretch
                  | `baseline
                ]
                  =?,
    ~aspectRatio: float=?,
    // border*Width are commented because already in view styles props (see explanation at the top)
    // ~borderBottomWidth: float=?,
    // ~borderEndWidth: float=?,
    // ~borderLeftWidth: float=?,
    // ~borderRightWidth: float=?,
    // ~borderStartWidth: float=?,
    // ~borderTopWidth: float=?,
    // ~borderWidth: float=?,
    ~bottom: size=?,
    ~direction: [@bs.string] [ | [@bs.as "inherit"] `inherit_ | `ltr | `rtl]=?,
    ~display: display=?,
    ~_end: size=?,
    ~flex: float=?,
    ~flexBasis: margin=?,
    ~flexDirection: [@bs.string] [
                      | `row
                      | [@bs.as "row-reverse"] `rowReverse
                      | `column
                      | [@bs.as "column-reverse"] `columnReverse
                    ]
                      =?,
    ~flexGrow: float=?,
    ~flexShrink: float=?,
    ~flexWrap: flexWrap=?,
    ~height: size=?,
    ~justifyContent: [@bs.string] [
                       | [@bs.as "flex-start"] `flexStart
                       | [@bs.as "flex-end"] `flexEnd
                       | `center
                       | [@bs.as "space-around"] `spaceAround
                       | [@bs.as "space-between"] `spaceBetween
                       | [@bs.as "space-evenly"] `spaceEvenly
                     ]
                       =?,
    ~left: size=?,
    ~margin: margin=?,
    ~marginBottom: margin=?,
    ~marginEnd: margin=?,
    ~marginHorizontal: margin=?,
    ~marginLeft: margin=?,
    ~marginRight: margin=?,
    ~marginStart: margin=?,
    ~marginTop: margin=?,
    ~marginVertical: margin=?,
    ~maxHeight: size=?,
    ~maxWidth: size=?,
    ~minHeight: size=?,
    ~minWidth: size=?,
    ~overflow: overflow=?,
    ~padding: size=?,
    ~paddingBottom: size=?,
    ~paddingEnd: size=?,
    ~paddingHorizontal: size=?,
    ~paddingLeft: size=?,
    ~paddingRight: size=?,
    ~paddingStart: size=?,
    ~paddingTop: size=?,
    ~paddingVertical: size=?,
    ~position: position=?,
    ~right: size=?,
    ~start: size=?,
    ~top: size=?,
    ~width: size=?,
    ~zIndex: int=?,
    unit
  ) =>
  t;

// ____TextStyleProp_Internal
[@bs.obj]
// Text Style Props (https://reactnative.dev/docs/text-style-props)
external textStyle:
  (
    ~color: Color.t=?,
    ~fontFamily: string=?,
    ~fontSize: float=?,
    ~fontStyle: fontStyle=?,
    ~fontVariant: array(FontVariant.t)=?,
    ~fontWeight: [@bs.string] [
                   | `normal
                   | `bold
                   | [@bs.as "100"] `_100
                   | [@bs.as "200"] `_200
                   | [@bs.as "300"] `_300
                   | [@bs.as "400"] `_400
                   | [@bs.as "500"] `_500
                   | [@bs.as "600"] `_600
                   | [@bs.as "700"] `_700
                   | [@bs.as "800"] `_800
                   | [@bs.as "900"] `_900
                 ]
                   =?,
    ~includeFontPadding: bool=?,
    ~letterSpacing: float=?,
    ~lineHeight: float=?,
    ~textAlign: textAlign=?,
    ~textAlignVertical: textAlignVertical=?,
    ~textDecorationColor: Color.t=?,
    ~textDecorationLine: [@bs.string] [
                           | `none
                           | `underline
                           | [@bs.as "line-through"] `lineThrough
                           | [@bs.as "underline line-through"]
                             `underlineLineThrough
                         ]
                           =?,
    ~textDecorationStyle: textDecorationStyle=?,
    ~textShadowColor: Color.t=?,
    ~textShadowOffset: offset=?,
    ~textShadowRadius: float=?,
    ~textTransform: textTransform=?,
    ~writingDirection: writingDirection=?,
    // View styles https://reactnative.dev/docs/view-style-props
    ~backfaceVisibility: backfaceVisibility=?,
    ~backgroundColor: Color.t=?,
    ~borderBottomColor: Color.t=?,
    ~borderBottomEndRadius: float=?,
    ~borderBottomLeftRadius: float=?,
    ~borderBottomRightRadius: float=?,
    ~borderBottomStartRadius: float=?,
    ~borderBottomWidth: float=?,
    ~borderColor: Color.t=?,
    ~borderEndColor: Color.t=?,
    ~borderEndWidth: float=?,
    ~borderLeftColor: Color.t=?,
    ~borderLeftWidth: float=?,
    ~borderRadius: float=?,
    ~borderRightColor: Color.t=?,
    ~borderRightWidth: float=?,
    ~borderStartColor: Color.t=?,
    ~borderStartWidth: float=?,
    ~borderStyle: borderStyle=?,
    ~borderTopColor: Color.t=?,
    ~borderTopEndRadius: float=?,
    ~borderTopLeftRadius: float=?,
    ~borderTopRightRadius: float=?,
    ~borderTopStartRadius: float=?,
    ~borderTopWidth: float=?,
    ~borderWidth: float=?,
    ~elevation: float=?,
    ~opacity: float=?,
    // Transform Props (https://reactnative.dev/docs/transforms#props)
    ~transform: array(transform)=?, // all other transform props are deprecated
    // Shadow Props (https://reactnative.dev/docs/shadow-props)
    ~shadowColor: Color.t=?,
    ~shadowOffset: offset=?,
    ~shadowOpacity: float=?,
    ~shadowRadius: float=?,
    // Layout Style Props (https://reactnative.dev/docs/layout-props)
    ~alignContent: [@bs.string] [
                     | [@bs.as "flex-start"] `flexStart
                     | [@bs.as "flex-end"] `flexEnd
                     | `center
                     | `stretch
                     | [@bs.as "space-around"] `spaceAround
                     | [@bs.as "space-between"] `spaceBetween
                   ]
                     =?,
    ~alignItems: [@bs.string] [
                   | [@bs.as "flex-start"] `flexStart
                   | [@bs.as "flex-end"] `flexEnd
                   | `center
                   | `stretch
                   | `baseline
                 ]
                   =?,
    ~alignSelf: [@bs.string] [
                  | `auto
                  | [@bs.as "flex-start"] `flexStart
                  | [@bs.as "flex-end"] `flexEnd
                  | `center
                  | `stretch
                  | `baseline
                ]
                  =?,
    ~aspectRatio: float=?,
    // border*Width are commented because already in view styles props (see explanation at the top)
    // ~borderBottomWidth: float=?,
    // ~borderEndWidth: float=?,
    // ~borderLeftWidth: float=?,
    // ~borderRightWidth: float=?,
    // ~borderStartWidth: float=?,
    // ~borderTopWidth: float=?,
    // ~borderWidth: float=?,
    ~bottom: size=?,
    ~direction: [@bs.string] [ | [@bs.as "inherit"] `inherit_ | `ltr | `rtl]=?,
    ~display: display=?,
    ~_end: size=?,
    ~flex: float=?,
    ~flexBasis: margin=?,
    ~flexDirection: [@bs.string] [
                      | `row
                      | [@bs.as "row-reverse"] `rowReverse
                      | `column
                      | [@bs.as "column-reverse"] `columnReverse
                    ]
                      =?,
    ~flexGrow: float=?,
    ~flexShrink: float=?,
    ~flexWrap: flexWrap=?,
    ~height: size=?,
    ~justifyContent: [@bs.string] [
                       | [@bs.as "flex-start"] `flexStart
                       | [@bs.as "flex-end"] `flexEnd
                       | `center
                       | [@bs.as "space-around"] `spaceAround
                       | [@bs.as "space-between"] `spaceBetween
                       | [@bs.as "space-evenly"] `spaceEvenly
                     ]
                       =?,
    ~left: size=?,
    ~margin: margin=?,
    ~marginBottom: margin=?,
    ~marginEnd: margin=?,
    ~marginHorizontal: margin=?,
    ~marginLeft: margin=?,
    ~marginRight: margin=?,
    ~marginStart: margin=?,
    ~marginTop: margin=?,
    ~marginVertical: margin=?,
    ~maxHeight: size=?,
    ~maxWidth: size=?,
    ~minHeight: size=?,
    ~minWidth: size=?,
    ~overflow: overflow=?,
    ~padding: size=?,
    ~paddingBottom: size=?,
    ~paddingEnd: size=?,
    ~paddingHorizontal: size=?,
    ~paddingLeft: size=?,
    ~paddingRight: size=?,
    ~paddingStart: size=?,
    ~paddingTop: size=?,
    ~paddingVertical: size=?,
    ~position: position=?,
    ~right: size=?,
    ~start: size=?,
    ~top: size=?,
    ~width: size=?,
    ~zIndex: int=?,
    unit
  ) =>
  t;

// ____ImageStyleProp_Internal
[@bs.obj]
// Image Style Props (https://reactnative.dev/docs/image-style-props)
external imageStyle:
  (
    ~resizeMode: resizeMode=?,
    ~overlayColor: Color.t=?,
    ~tintColor: Color.t=?,
    // View styles https://reactnative.dev/docs/view-style-props
    ~backfaceVisibility: backfaceVisibility=?,
    ~backgroundColor: Color.t=?,
    ~borderBottomColor: Color.t=?,
    ~borderBottomEndRadius: float=?,
    ~borderBottomLeftRadius: float=?,
    ~borderBottomRightRadius: float=?,
    ~borderBottomStartRadius: float=?,
    ~borderBottomWidth: float=?,
    ~borderColor: Color.t=?,
    ~borderEndColor: Color.t=?,
    ~borderEndWidth: float=?,
    ~borderLeftColor: Color.t=?,
    ~borderLeftWidth: float=?,
    ~borderRadius: float=?,
    ~borderRightColor: Color.t=?,
    ~borderRightWidth: float=?,
    ~borderStartColor: Color.t=?,
    ~borderStartWidth: float=?,
    ~borderStyle: borderStyle=?,
    ~borderTopColor: Color.t=?,
    ~borderTopEndRadius: float=?,
    ~borderTopLeftRadius: float=?,
    ~borderTopRightRadius: float=?,
    ~borderTopStartRadius: float=?,
    ~borderTopWidth: float=?,
    ~borderWidth: float=?,
    ~elevation: float=?,
    ~opacity: float=?,
    // Transform Props (https://reactnative.dev/docs/transforms#props)
    ~transform: array(transform)=?, // all other transform props are deprecated
    // Shadow Props (https://reactnative.dev/docs/shadow-props)
    ~shadowColor: Color.t=?,
    ~shadowOffset: offset=?,
    ~shadowOpacity: float=?,
    ~shadowRadius: float=?,
    // Layout Style Props (https://reactnative.dev/docs/layout-props)
    ~alignContent: [@bs.string] [
                     | [@bs.as "flex-start"] `flexStart
                     | [@bs.as "flex-end"] `flexEnd
                     | `center
                     | `stretch
                     | [@bs.as "space-around"] `spaceAround
                     | [@bs.as "space-between"] `spaceBetween
                   ]
                     =?,
    ~alignItems: [@bs.string] [
                   | [@bs.as "flex-start"] `flexStart
                   | [@bs.as "flex-end"] `flexEnd
                   | `center
                   | `stretch
                   | `baseline
                 ]
                   =?,
    ~alignSelf: [@bs.string] [
                  | `auto
                  | [@bs.as "flex-start"] `flexStart
                  | [@bs.as "flex-end"] `flexEnd
                  | `center
                  | `stretch
                  | `baseline
                ]
                  =?,
    ~aspectRatio: float=?,
    // border*Width are commented because already in view styles props (see explanation at the top)
    // ~borderBottomWidth: float=?,
    // ~borderEndWidth: float=?,
    // ~borderLeftWidth: float=?,
    // ~borderRightWidth: float=?,
    // ~borderStartWidth: float=?,
    // ~borderTopWidth: float=?,
    // ~borderWidth: float=?,
    ~bottom: size=?,
    ~direction: [@bs.string] [ | [@bs.as "inherit"] `inherit_ | `ltr | `rtl]=?,
    ~display: display=?,
    ~_end: size=?,
    ~flex: float=?,
    ~flexBasis: margin=?,
    ~flexDirection: [@bs.string] [
                      | `row
                      | [@bs.as "row-reverse"] `rowReverse
                      | `column
                      | [@bs.as "column-reverse"] `columnReverse
                    ]
                      =?,
    ~flexGrow: float=?,
    ~flexShrink: float=?,
    ~flexWrap: flexWrap=?,
    ~height: size=?,
    ~justifyContent: [@bs.string] [
                       | [@bs.as "flex-start"] `flexStart
                       | [@bs.as "flex-end"] `flexEnd
                       | `center
                       | [@bs.as "space-around"] `spaceAround
                       | [@bs.as "space-between"] `spaceBetween
                       | [@bs.as "space-evenly"] `spaceEvenly
                     ]
                       =?,
    ~left: size=?,
    ~margin: margin=?,
    ~marginBottom: margin=?,
    ~marginEnd: margin=?,
    ~marginHorizontal: margin=?,
    ~marginLeft: margin=?,
    ~marginRight: margin=?,
    ~marginStart: margin=?,
    ~marginTop: margin=?,
    ~marginVertical: margin=?,
    ~maxHeight: size=?,
    ~maxWidth: size=?,
    ~minHeight: size=?,
    ~minWidth: size=?,
    ~overflow: overflow=?,
    ~padding: size=?,
    ~paddingBottom: size=?,
    ~paddingEnd: size=?,
    ~paddingHorizontal: size=?,
    ~paddingLeft: size=?,
    ~paddingRight: size=?,
    ~paddingStart: size=?,
    ~paddingTop: size=?,
    ~paddingVertical: size=?,
    ~position: position=?,
    ~right: size=?,
    ~start: size=?,
    ~top: size=?,
    ~width: size=?,
    ~zIndex: int=?,
    unit
  ) =>
  t;
