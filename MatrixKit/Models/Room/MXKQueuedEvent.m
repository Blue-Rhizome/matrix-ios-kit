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

#import "MXKQueuedEvent.h"

@implementation MXKQueuedEvent

- (instancetype)initWithEvent:(MXEvent *)event andRoomState:(MXRoomState *)state direction:(MXEventDirection)direction
{
    self = [super init];
    if (self) {
        // Make a copy as the data can be read at anytime later
        _event = [event copy];
        _state = [state copy];
        _direction = direction;
    }
    return self;
}

@end