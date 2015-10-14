/*
 Copyright 2015 OpenMarket Ltd

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */

#import <Foundation/Foundation.h>

#import <MatrixSDK/MatrixSDK.h>

#import "MXKResponderRageShaking.h"

/**
 `MXKViewControllerHandling` defines a protocol to handle requirements for
 all matrixKit view controllers and table view controllers.
 
 It manages the following points:
 - matrix sessions handling, one or more sessions are supported.
 - stop/start activity indicator according to the state of the associated matrix sessions.
 - update view appearance on matrix session state change.
 - support rage shake mechanism (depend on `rageShakeManager` property).
 */
@protocol MXKViewControllerHandling <NSObject>

/**
 List of associated matrix sessions (empty by default).
 This property is used to update view appearance according to the session(s) state.
 */
@property (nonatomic, readonly) NSArray* mxSessions;

/**
 The first associated matrix session is considered as the main session (nil by default).
 */
@property (nonatomic, readonly) MXSession *mainSession;

/**
 Keep reference on the pushed and/or presented view controllers.
 */
@property (nonatomic, readonly) NSArray *childViewControllers;

/**
 An object implementing the `MXKResponderRageShaking` protocol.
 The view controller uses this object (if any) to report beginning and end of potential
 rage shake when it is the first responder.
 
 This property is nil by default.
 */
@property (nonatomic) id<MXKResponderRageShaking> rageShakeManager;

/**
 Activity indicator view.
 By default this activity indicator is centered inside the view controller view. It is automatically
 start on the following matrix session states: `MXSessionStateInitialised` and `MXSessionStateSyncInProgress`.
 It is stopped on other states.
 Set nil to disable activity indicator animation.
 */
@property (nonatomic) UIActivityIndicatorView *activityIndicator;

/**
 Add/remove matrix session.
 
 @param mxSession a Matrix session.
 */
- (void)addMatrixSession:(MXSession*)mxSession;
- (void)removeMatrixSession:(MXSession*)mxSession;

/**
 This method is called on the following matrix session changes:
 - a new session is added.
 - a session is removed.
 - the state of an associated session changed (according to `MXSessionStateDidChangeNotification`).
 
 This method is called to refresh the display when the view controller will appear too.
 
 By default view controller appearance is updated according to the state of associated sessions:
 - starts activity indicator as soon as at least one session state is `MXSessionStateInitialised` or `MXSessionStateSyncInProgress`.
 - switches in red the navigation bar tintColor when all sessions are in `MXSessionStateHomeserverNotReachable` state.
 - switches in orange the navigation bar tintColor when at least one session is in `MXSessionStateHomeserverNotReachable` state.
 
 Override it to customize view appearance according to associated session(s).
 */
- (void)onMatrixSessionChange;

/**
 Pop or dismiss the view controller. It depends if the view controller is embedded inside a navigation controller or not.
 
 @param animated YES to animate the transition.
 @param completion the block to execute after the view controller is popped or dismissed. This block has no return value and takes no parameters. You may specify nil for this parameter.
 */
- (void)withdrawViewControllerAnimated:(BOOL)animated completion:(void (^)(void))completion;

/**
 Dispose of any resources, and remove event observers.
 */
- (void)destroy;

/**
 Bring the activity indicator to the front and start it.
 */
- (void)startActivityIndicator;

/**
 Stop the activity indicator if all conditions are satisfied.
 */
- (void)stopActivityIndicator;

@end
