
#pragma once

#include "types.h"

#include <zsLib/types.h>
#include <map>

#define WRAPPER_DEPROXIFY_CLASS(xProxyClass, xDerivedClassType, xPtr) \
        ::wrapper::impl::org::webRtc::deproxifyClass<xDerivedClassType, xProxyClass##Proxy, xProxyClass##Interface>(xPtr)

namespace wrapper {
  namespace impl {
    namespace org {
      namespace webRtc {

        //---------------------------------------------------------------------
        //---------------------------------------------------------------------
        //---------------------------------------------------------------------
        //---------------------------------------------------------------------
        //
        // (helper functions)
        //

        //---------------------------------------------------------------------
        template<class xDerivedClassType, class XProxyType, class XOriginalInterfaceType>
        ZS_NO_DISCARD() XOriginalInterfaceType *deproxifyClass(XOriginalInterfaceType *possibleProxy) noexcept
        {
          do
          {
            XProxyType *proxy = dynamic_cast<XProxyType *>(possibleProxy);
            if (!proxy) break;
            auto temp = proxy->internal();
            if (!temp) return possibleProxy;
            possibleProxy = dynamic_cast<xDerivedClassType *>(temp);
            if (!possibleProxy) return temp;
          } while (true);
          return possibleProxy;
        }

        //---------------------------------------------------------------------
        //---------------------------------------------------------------------
        //---------------------------------------------------------------------
        //---------------------------------------------------------------------
        //
        // WrapperMapper
        //
        template<class XInterfaceType, class XWrapperImplType>
        class WrapperMapper
        {
        public:
          ZS_DECLARE_TYPEDEF_PTR(XWrapperImplType, WrapperImplType);
          typedef XInterfaceType NativeType;

          typedef std::map<NativeType *, WrapperImplTypeWeakPtr> NativeWrapperMap;

          //-------------------------------------------------------------------
          WrapperImplTypePtr getExistingOrCreateNew(
                                                    NativeType *native,
                                                    std::function<WrapperImplTypePtr()> creatorFunc
                                                    ) noexcept
          {
            zsLib::AutoLock lock(lock_);

            {
              auto found = map_.find(native);
              if (found != map_.end()) {
                auto &weak = found->second;
                auto strong = weak.lock();
                if (!strong) goto create_new_entry;
                return strong;
              }
            }

          create_new_entry:
            auto temp = creatorFunc();
            map_[native] = temp;
            return temp;
          }

          //-------------------------------------------------------------------
          void remove(NativeType *native)
          {
            if (!native) return;
            zsLib::AutoLock lock(lock_);
            map_.erase(native);
          }

        private:
          zsLib::Lock lock_;
          NativeWrapperMap map_;
        };

      } // webRtc
    } // org
  } // namespace impl
} // namespace wrapper

