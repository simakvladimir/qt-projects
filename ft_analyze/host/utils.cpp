#include "utils.h"



namespace IntelUtils {

    cl_platform_id getIntelOCLPlatform()
    {
        cl_platform_id pPlatforms[10] = { 0 };
        char pPlatformName[128] = { 0 };

        cl_uint uiPlatformsCount = 0;
        cl_int err = clGetPlatformIDs(10, pPlatforms, &uiPlatformsCount);
        for (cl_uint ui = 0; ui < uiPlatformsCount; ++ui)
        {
            err = clGetPlatformInfo(pPlatforms[ui], CL_PLATFORM_NAME, 128 * sizeof(char), pPlatformName, NULL);
            if ( err != CL_SUCCESS )
            {
                return NULL;
            }

            if (!strcmp(pPlatformName, "Intel(R) OpenCL"))
                return pPlatforms[ui];
        }

        return NULL;
    }

}
