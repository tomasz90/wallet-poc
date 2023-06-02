// Copyright © 2017-2023 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

use std::ffi::c_char;

pub const OK_CODE: ErrorCode = 0;
pub const UNKNOWN_ERROR: ErrorCode = -1;

pub type ErrorCode = i32;

#[macro_export]
macro_rules! impl_c_result {
    ($name:ident, $result:ty, $default:expr) => {
        impl $name {
            pub fn ok(result: $result) -> $name {
                $name {
                    code: $crate::ffi::c_result::OK_CODE,
                    result,
                }
            }

            pub fn error<E>(code: E) -> $name
            where
                $crate::ffi::c_result::ErrorCode: From<E>,
            {
                let mut code = $crate::ffi::c_result::ErrorCode::from(code);
                if (code == $crate::ffi::c_result::OK_CODE) {
                    code = $crate::ffi::c_result::UNKNOWN_ERROR;
                }
                $name {
                    code,
                    result: $default,
                }
            }

            pub fn is_ok(&self) -> bool {
                self.code == $crate::ffi::c_result::OK_CODE
            }

            pub fn is_err(&self) -> bool {
                !self.is_ok()
            }

            pub fn into_result(self) -> Result<$result, $crate::ffi::c_result::ErrorCode> {
                if self.is_ok() {
                    Ok(self.result)
                } else {
                    Err(self.code)
                }
            }

            #[track_caller]
            pub fn unwrap(self) -> $result {
                if !self.is_ok() {
                    panic!(
                        "called `{}::unwrap()` on an error: {}",
                        stringify!($name),
                        self.code
                    );
                }
                self.result
            }
        }

        impl<E> From<core::result::Result<$result, E>> for $name
        where
            $crate::ffi::c_result::ErrorCode: From<E>,
        {
            fn from(res: core::result::Result<$result, E>) -> Self {
                match res {
                    Ok(ready) => $name::ok(ready),
                    Err(error) => $name::error(error),
                }
            }
        }
    };
}

#[repr(C)]
pub struct CStrResult {
    pub code: i32,
    pub result: *const c_char,
}

#[repr(C)]
pub struct CStrMutResult {
    pub code: i32,
    pub result: *mut c_char,
}

#[repr(C)]
pub struct CBoolResult {
    pub code: i32,
    pub result: bool,
}

impl_c_result!(CStrResult, *const c_char, core::ptr::null());
impl_c_result!(CStrMutResult, *mut c_char, core::ptr::null_mut());
impl_c_result!(CBoolResult, bool, false);
