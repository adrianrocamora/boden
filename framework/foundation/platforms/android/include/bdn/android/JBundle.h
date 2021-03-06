#ifndef BDN_ANDROID_JBundle_H_
#define BDN_ANDROID_JBundle_H_

#include <bdn/android/JBaseBundle.h>
#include <bdn/java/JCharSequence.h>
#include <bdn/java/JString.h>

namespace bdn
{
    namespace android
    {

        /** Accessor for Java android.os.Bundle objects.*/
        class JBundle : public bdn::android::JBaseBundle
        {
          public:
            /** @param javaRef the reference to the Java object.
             *      The JObject instance will copy this reference and keep its
             * type. So if you want the JObject instance to hold a strong
             * reference then you need to call toStrong() on the reference first
             * and pass the result.
             *      */
            explicit JBundle(const bdn::java::Reference &javaRef) : JBaseBundle(javaRef) {}

            /** Returns the JClass object for this class.
             *
             *  Note that the returned class object is not necessarily unique
             * for the whole process. You might get different objects if this
             * function is called from different shared libraries.
             *
             *  If you want to check for type equality then you should compare
             * the type name (see getTypeName() )
             *  */
            static bdn::java::JClass &getStaticClass_()
            {
                static bdn::java::JClass cls("android/os/Bundle");

                return cls;
            }

            bdn::java::JClass &getClass_() override { return getStaticClass_(); }
        };
    }
}

#endif
