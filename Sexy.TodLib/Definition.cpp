#include "Trail.h"
#include <assert.h>
#include "TodDebug.h"
#include "Definition.h"
#include "../ImageLib/zlib/zlib.h"
#include "../PakLib/PakInterface.h"
#include "../SexyAppFramework/PerfTimer.h"
#include "../SexyAppFramework/XMLParser.h"

DefSymbol gTrailFlagDefSymbols[] = {  
    { 0, "Loops" },                 { -1, nullptr }
};
DefField gTrailDefFields[] = {  
    { "Image",              0x0,        DefFieldType::DT_IMAGE,         nullptr },
    { "MaxPoints",          0x4,        DefFieldType::DT_INT,           nullptr },
    { "MinPointDistance",   0x8,        DefFieldType::DT_FLOAT,         nullptr },
    { "TrailFlags",         0xC,        DefFieldType::DT_FLAGS,         gTrailFlagDefSymbols },
    { "WidthOverLength",    0x18,       DefFieldType::DT_TRACK_FLOAT,   nullptr },
    { "WidthOverTime",      0x20,       DefFieldType::DT_TRACK_FLOAT,   nullptr },
    { "AlphaOverLength",    0x28,       DefFieldType::DT_TRACK_FLOAT,   nullptr },
    { "AlphaOverTime",      0x30,       DefFieldType::DT_TRACK_FLOAT,   nullptr },
    { "TrailDuration",      0x10,       DefFieldType::DT_TRACK_FLOAT,   nullptr },
    { "",                   0x0,        DefFieldType::DT_INVALID,       nullptr }
};
DefMap gTrailDefMap = { gTrailDefFields, sizeof(TrailDefinition), TrailDefinitionConstructor };  

DefSymbol gParticleFlagSymbols[] = {  
    {  0, "RandomLaunchSpin" },     {  1, "AlignLaunchSpin" },  {  2, "AlignToPixel" },     {  4, "ParticleLoops" },    {  3, "SystemLoops" },
    {  5, "ParticlesDontFollow" },  {  6, "RandomStartTime" },  {  7, "DieIfOverloaded" },  {  8, "Additive" },         {  9, "FullScreen" },
    { 10, "SoftwareOnly" },         { 11, "HardwareOnly" },     { -1, nullptr }
};
DefSymbol gEmitterTypeSymbols[] = {  
    {  0, "Circle" },               {  1, "Box" },              {  2, "BoxPath" },          {  3, "CirclePath" },       {  4, "CircleEvenSpacing" },
    { -1, nullptr }
};
DefSymbol gParticleTypeSymbols[] = {  
    {  1, "Friction" },             {  2, "Acceleration" },     {  3, "Attractor" },        {  4, "MaxVelocity" },      {  5, "Velocity" },
    {  6, "Position" },             {  7, "SystemPosition" },   {  8, "GroundConstraint" }, {  9, "Shake" },            { 10, "Circle" },
    { 11, "Away" },                 { -1, nullptr }
};

DefField gParticleFieldDefFields[] = {  
    { "FieldType",          0x0,        DefFieldType::DT_ENUM,          gParticleTypeSymbols },
    { "x",                  0x4,        DefFieldType::DT_TRACK_FLOAT,   nullptr },
    { "y",                  0xC,        DefFieldType::DT_TRACK_FLOAT,   nullptr },
    { "",                   0x0,        DefFieldType::DT_INVALID,       nullptr },
};
DefMap gParticleFieldDefMap = { gParticleFieldDefFields, sizeof(ParticleField), ParticleFieldConstructor };  

DefField gEmitterDefFields[] = {  
    { "Image",              0x0,        DefFieldType::DT_IMAGE,         nullptr },
    { "ImageRow",           0x8,        DefFieldType::DT_INT,           nullptr },
    { "ImageCol",           0x4,        DefFieldType::DT_INT,           nullptr },
    { "ImageFrames",        0xC,        DefFieldType::DT_INT,           nullptr },
    { "Animated",           0x10,       DefFieldType::DT_INT,           nullptr },
    { "ParticleFlags",      0x14,       DefFieldType::DT_FLAGS,         gParticleFlagSymbols },
    { "EmitterType",        0x18,       DefFieldType::DT_ENUM,          gEmitterTypeSymbols },
    { "Name",               0x1C,       DefFieldType::DT_STRING,        nullptr },
    { "SystemDuration",     0x24,       DefFieldType::DT_TRACK_FLOAT,   nullptr },
    { "OnDuration",         0x20,       DefFieldType::DT_STRING,        nullptr },
    { "CrossFadeDuration",  0x2C,       DefFieldType::DT_TRACK_FLOAT,   nullptr },
    { "SpawnRate",          0x34,       DefFieldType::DT_TRACK_FLOAT,   nullptr },
    { "SpawnMinActive",     0x3C,       DefFieldType::DT_TRACK_FLOAT,   nullptr },
    { "SpawnMaxActive",     0x44,       DefFieldType::DT_TRACK_FLOAT,   nullptr },
    { "SpawnMaxLaunched",   0x4C,       DefFieldType::DT_TRACK_FLOAT,   nullptr },
    { "EmitterRadius",      0x54,       DefFieldType::DT_TRACK_FLOAT,   nullptr },
    { "EmitterOffsetX",     0x5C,       DefFieldType::DT_TRACK_FLOAT,   nullptr },
    { "EmitterOffsetY",     0x64,       DefFieldType::DT_TRACK_FLOAT,   nullptr },
    { "EmitterBoxX",        0x6C,       DefFieldType::DT_TRACK_FLOAT,   nullptr },
    { "EmitterBoxY",        0x74,       DefFieldType::DT_TRACK_FLOAT,   nullptr },
    { "EmitterPath",        0x8C,       DefFieldType::DT_TRACK_FLOAT,   nullptr },
    { "EmitterSkewX",       0x7C,       DefFieldType::DT_TRACK_FLOAT,   nullptr },
    { "EmitterSkewY",       0x84,       DefFieldType::DT_TRACK_FLOAT,   nullptr },
    { "ParticleDuration",   0x94,       DefFieldType::DT_TRACK_FLOAT,   nullptr },
    { "SystemRed",          0xAC,       DefFieldType::DT_TRACK_FLOAT,   nullptr },
    { "SystemGreen",        0xB4,       DefFieldType::DT_TRACK_FLOAT,   nullptr },
    { "SystemBlue",         0xBC,       DefFieldType::DT_TRACK_FLOAT,   nullptr },
    { "SystemAlpha",        0xC4,       DefFieldType::DT_TRACK_FLOAT,   nullptr },
    { "SystemBrightness",   0xCC,       DefFieldType::DT_TRACK_FLOAT,   nullptr },
    { "LaunchSpeed",        0x9C,       DefFieldType::DT_TRACK_FLOAT,   nullptr },
    { "LaunchAngle",        0xA4,       DefFieldType::DT_TRACK_FLOAT,   nullptr },
    { "Field",              0xD4,       DefFieldType::DT_ARRAY,         &gParticleFieldDefMap },
    { "SystemField",        0xDC,       DefFieldType::DT_ARRAY,         &gParticleFieldDefMap },
    { "ParticleRed",        0xE4,       DefFieldType::DT_TRACK_FLOAT,   nullptr },
    { "ParticleGreen",      0xEC,       DefFieldType::DT_TRACK_FLOAT,   nullptr },
    { "ParticleBlue",       0xF4,       DefFieldType::DT_TRACK_FLOAT,   nullptr },
    { "ParticleAlpha",      0xFC,       DefFieldType::DT_TRACK_FLOAT,   nullptr },
    { "ParticleBrightness", 0x104,      DefFieldType::DT_TRACK_FLOAT,   nullptr },
    { "ParticleSpinAngle",  0x10C,      DefFieldType::DT_TRACK_FLOAT,   nullptr },
    { "ParticleSpinSpeed",  0x114,      DefFieldType::DT_TRACK_FLOAT,   nullptr },
    { "ParticleScale",      0x11C,      DefFieldType::DT_TRACK_FLOAT,   nullptr },
    { "ParticleStretch",    0x124,      DefFieldType::DT_TRACK_FLOAT,   nullptr },
    { "CollisionReflect",   0x12C,      DefFieldType::DT_TRACK_FLOAT,   nullptr },
    { "CollisionSpin",      0x134,      DefFieldType::DT_TRACK_FLOAT,   nullptr },
    { "ClipTop",            0x13C,      DefFieldType::DT_TRACK_FLOAT,   nullptr },
    { "ClipBottom",         0x144,      DefFieldType::DT_TRACK_FLOAT,   nullptr },
    { "ClipLeft",           0x14C,      DefFieldType::DT_TRACK_FLOAT,   nullptr },
    { "ClipRight",          0x154,      DefFieldType::DT_TRACK_FLOAT,   nullptr },
    { "AnimationRate",      0x15C,      DefFieldType::DT_TRACK_FLOAT,   nullptr },
    { "",                   0x0,        DefFieldType::DT_INVALID,       nullptr },
};
DefMap gEmitterDefMap = { gEmitterDefFields, sizeof(TodEmitterDefinition), TodEmitterDefinitionConstructor };  

DefField gParticleDefFields[] = {  
    { "Emitter",            0x0,        DefFieldType::DT_ARRAY,         &gEmitterDefMap },
    { "",                   0x0,        DefFieldType::DT_INVALID,       nullptr }
};
DefMap gParticleDefMap = { gParticleDefFields, sizeof(TodParticleDefinition), TodParticleDefinitionConstructor };  

DefField gReanimatorTransformDefFields[] = {  
    { "x",                  0x0,        DefFieldType::DT_FLOAT,         nullptr },
    { "y",                  0x4,        DefFieldType::DT_FLOAT,         nullptr },
    { "kx",                 0x8,        DefFieldType::DT_FLOAT,         nullptr },
    { "kx",                 0xC,        DefFieldType::DT_FLOAT,         nullptr },
    { "sx",                 0x10,       DefFieldType::DT_FLOAT,         nullptr },
    { "sx",                 0x14,       DefFieldType::DT_FLOAT,         nullptr },
    { "f",                  0x18,       DefFieldType::DT_FLOAT,         nullptr },
    { "a",                  0x1C,       DefFieldType::DT_FLOAT,         nullptr },
    { "i",                  0x20,       DefFieldType::DT_IMAGE,         nullptr },
    { "font",               0x24,       DefFieldType::DT_FONT,          nullptr },
    { "text",               0x28,       DefFieldType::DT_STRING,        nullptr },
    { "",                   0x0,        DefFieldType::DT_INVALID,       nullptr }
};
DefMap gReanimatorTransformDefMap = { gReanimatorTransformDefFields, sizeof(ReanimatorTransform), };  

DefField gReanimatorTrackDefFields[] = {  
    { "name",               0x0,        DefFieldType::DT_STRING,        nullptr },
    { "t",                  0x4,        DefFieldType::DT_ARRAY,         &gReanimatorTransformDefMap },
    { "",                   0x0,        DefFieldType::DT_INVALID,       nullptr }
};
DefMap gReanimatorTrackDefMap = { gReanimatorTrackDefFields, sizeof(ReanimatorTrack), ReanimatorTrackConstructor };  

DefField gReanimatorDefFields[] = {
    { "track",              0x0,        DefFieldType::DT_ARRAY,         &gReanimatorTrackDefMap },
    { "fps",                0x8,        DefFieldType::DT_FLOAT,         nullptr },
    { "",                   0x0,        DefFieldType::DT_INVALID,       nullptr }
};  
DefMap gReanimatorDefMap = { gReanimatorDefFields, sizeof(ReanimatorDefinition), ReanimatorDefinitionConstructor };  

static DefLoadResPath gDefLoadResPaths[4] = { {"IMAGE_", ""}, {"IMAGE_", "particles\\"}, {"IMAGE_REANIM_", "reanim\\"}, {"IMAGE_REANIM_", "images\\"} };  

void* ParticleFieldConstructor(void* thePointer)
{
    if (thePointer)
    {
        ((ParticleField*)thePointer)->mX.mNodes = nullptr;
        ((ParticleField*)thePointer)->mX.mCountNodes = 0;
        ((ParticleField*)thePointer)->mY.mNodes = nullptr;
        ((ParticleField*)thePointer)->mY.mCountNodes = 0;
        ((ParticleField*)thePointer)->mFieldType = ParticleFieldType::FIELD_INVALID;
    }
    return thePointer;
}

void* TodEmitterDefinitionConstructor(void* thePointer)
{
    if (thePointer)
    {
        memset(thePointer, NULL, sizeof(TodEmitterDefinition));
        ((TodEmitterDefinition*)thePointer)->mImageFrames = 1;
        ((TodEmitterDefinition*)thePointer)->mEmitterType = EmitterType::EMITTER_BOX;
        ((TodEmitterDefinition*)thePointer)->mName = "";
        ((TodEmitterDefinition*)thePointer)->mOnDuration = "";
        ((TodEmitterDefinition*)thePointer)->mImageRow = 0;
        ((TodEmitterDefinition*)thePointer)->mImageCol = 0;
        ((TodEmitterDefinition*)thePointer)->mAnimated = 0;
        ((TodEmitterDefinition*)thePointer)->mImage = nullptr;
    }
    return thePointer;
}

void* TodParticleDefinitionConstructor(void* thePointer)
{
    if (thePointer)
    {
        ((TodParticleDefinition*)thePointer)->mEmitterDefs = nullptr;
        ((TodParticleDefinition*)thePointer)->mEmitterDefCount = 0;
    }
    return thePointer;
}

void* TrailDefinitionConstructor(void* thePointer)
{
    if (thePointer)
    {
        memset(thePointer, 0, sizeof(TrailDefinition));
        ((TrailDefinition*)thePointer)->mMinPointDistance = 1.0f;
        ((TrailDefinition*)thePointer)->mMaxPoints = 2;
        ((TrailDefinition*)thePointer)->mTrailFlags = 0U;
        ((TrailDefinition*)thePointer)->mImage = nullptr;
    }
    return thePointer;
}

void* ReanimatorTransformConstructor(void* thePointer)
{
    if (thePointer)
    {
        ((ReanimatorTransform*)thePointer)->mTransX = DEFAULT_FIELD_PLACEHOLDER;
        ((ReanimatorTransform*)thePointer)->mTransY = DEFAULT_FIELD_PLACEHOLDER;
        ((ReanimatorTransform*)thePointer)->mSkewX = DEFAULT_FIELD_PLACEHOLDER;
        ((ReanimatorTransform*)thePointer)->mSkewY = DEFAULT_FIELD_PLACEHOLDER;
        ((ReanimatorTransform*)thePointer)->mScaleX = DEFAULT_FIELD_PLACEHOLDER;
        ((ReanimatorTransform*)thePointer)->mScaleY = DEFAULT_FIELD_PLACEHOLDER;
        ((ReanimatorTransform*)thePointer)->mFrame = DEFAULT_FIELD_PLACEHOLDER;
        ((ReanimatorTransform*)thePointer)->mAlpha = DEFAULT_FIELD_PLACEHOLDER;
        ((ReanimatorTransform*)thePointer)->mImage = nullptr;
        ((ReanimatorTransform*)thePointer)->mFont = nullptr;
        ((ReanimatorTransform*)thePointer)->mText = "";
    }
    return thePointer;
}

void* ReanimatorTrackConstructor(void* thePointer)
{
    if (thePointer)
    {
        ((ReanimatorTrack*)thePointer)->mName = "";
        ((ReanimatorTrack*)thePointer)->mTransforms = nullptr;
        ((ReanimatorTrack*)thePointer)->mTransformCount = 0;
    }
    return thePointer;
}

void* ReanimatorDefinitionConstructor(void* thePointer)
{
    if (thePointer)
    {
        ((ReanimatorDefinition*)thePointer)->mTracks = nullptr;
        ((ReanimatorDefinition*)thePointer)->mTrackCount = 0;
        ((ReanimatorDefinition*)thePointer)->mFPS = 12.0f;
        ((ReanimatorDefinition*)thePointer)->mReanimAtlas = nullptr;
    }
    return thePointer;
}

void* DefinitionAlloc(int theSize)
{
    void* aPtr = operator new[](theSize);
    TOD_ASSERT(aPtr);
    memset(aPtr, 0, theSize);
    return aPtr;
}

bool DefinitionLoadImage(Image** theImage, const SexyString& theName)
{
    if (theName.size() == 0)
    {
        *theImage = nullptr;
        return true;
    }

    Image* anImage = (Image*)gSexyAppBase->mResourceManager->LoadImage(theName);
    if (anImage)
    {
        *theImage = anImage;
        return true;
    }

    for (const DefLoadResPath& aLoadResPath : gDefLoadResPaths)
    {
        int aNameLen = theName.size();
        int aPrefixLen = strlen(aLoadResPath.mPrefix);
        if (aPrefixLen < aNameLen)
        {
            SexyString aPathToTry = aLoadResPath.mDirectory + theName.substr(aPrefixLen, aNameLen);
            SharedImageRef aImageRef = gSexyAppBase->GetSharedImage(aPathToTry);
            if ((Image*)aImageRef != nullptr)
            {
                TodHesitationTrace("Load Image '%s'", theName.c_str());
                TodAddImageToMap(&aImageRef, theName);
                TodMarkImageForSanding((Image*)aImageRef);
                *theImage = (Image*)aImageRef;
                return true;
            }
        }
    }
    return false;
}

bool DefinitionLoadFont(Font** theFont, const SexyString& theName)
{
    Font* aFont = gSexyAppBase->mResourceManager->LoadFont(SexyStringToString(theName));
    *theFont = aFont;
    return aFont != nullptr;
}

bool DefinitionLoadXML(const SexyString& theFileName, DefMap* theDefMap, void* theDefinition)
{
    return DefinitionCompileAndLoad(theFileName, theDefMap, theDefinition);
}

void SMemR(void*& _Src, void* _Dst, size_t _Size)
{
    memcpy(_Dst, _Src, _Size);
    _Src = (void*)((unsigned int)_Src + _Size);
}
bool DefReadFromCacheArray(void*& theReadPtr, DefinitionArrayDef* theArray, DefMap* theDefMap)
{
    int aDefSize;
    SMemR(theReadPtr, &aDefSize, sizeof(int));  
    if (aDefSize != theDefMap->mDefSize)  
    {
        TodTrace("cache has old def: array size");
        return false;
    }
    if (theArray->mArrayCount == 0)  
        return true;

    int aArraySize = aDefSize * theArray->mArrayCount;
    void* pData = DefinitionAlloc(aArraySize);  
    theArray->mArrayData = pData;
    SMemR(theReadPtr, pData, aArraySize);  
    for (int i = 0; i < theArray->mArrayCount; i++)
        if (!DefMapReadFromCache(theReadPtr, theDefMap, (void*)((int)pData + theDefMap->mDefSize * i)))  
            return false;
    return true;
}

bool DefReadFromCacheFloatTrack(void*& theReadPtr, FloatParameterTrack* theTrack)
{
    int& aCountNodes = theTrack->mCountNodes;
    SMemR(theReadPtr, &aCountNodes, sizeof(int));
    if (aCountNodes > 0)
    {
        int aSize = aCountNodes * sizeof(FloatParameterTrackNode);
        FloatParameterTrackNode* aPtr = (FloatParameterTrackNode*)DefinitionAlloc(aSize);
        theTrack->mNodes = aPtr;
        SMemR(theReadPtr, aPtr, aSize);
    }
    return true;
}

bool DefReadFromCacheString(void*& theReadPtr, char** theString)
{
    int aLen;
    SMemR(theReadPtr, &aLen, sizeof(int));
    TOD_ASSERT(aLen >= 0 && aLen <= 100000);
    if (aLen == 0)
        *theString = "";
    else
    {
        char* aPtr = (char*)DefinitionAlloc(aLen + 1);
        *theString = aPtr;
        SMemR(theReadPtr, aPtr, aLen);
        aPtr[aLen] = '\0';
    }
    return true;
}

bool DefReadFromCacheImage(void*& theReadPtr, Image** theImage)
{
    int aLen;
    SMemR(theReadPtr, &aLen, sizeof(int));  
    char* aImageName = (char*)_alloca(aLen + 1);  
    SMemR(theReadPtr, aImageName, aLen);  
    aImageName[aLen] = '\0';

    *theImage = nullptr;
    return aImageName[0] == '\0' || DefinitionLoadImage(theImage, aImageName);
}

bool DefReadFromCacheFont(void*& theReadPtr, Font** theFont)
{
    int aLen;
    SMemR(theReadPtr, &aLen, sizeof(int));  
    char* aFontName = (char*)_alloca(aLen + 1);  
    SMemR(theReadPtr, aFontName, aLen);  
    aFontName[aLen] = '\0';

    *theFont = nullptr;
    return aFontName[0] == '\0' || DefinitionLoadFont(theFont, aFontName);
}

bool DefMapReadFromCache(void*& theReadPtr, DefMap* theDefMap, void* theDefinition)
{
    for (DefField* aField = theDefMap->mMapFields; *aField->mFieldName != '\0'; aField++)
    {
        bool aSucceed = true;
        void* aDest = (void*)((int)theDefinition + aField->mFieldOffset);  
        switch (aField->mFieldType)
        {
        case DefFieldType::DT_STRING:
            aSucceed = DefReadFromCacheString(theReadPtr, (char**)aDest);
            break;
        case DefFieldType::DT_ARRAY:
            aSucceed = DefReadFromCacheArray(theReadPtr, (DefinitionArrayDef*)aDest, (DefMap*)aField->mExtraData);
            break;
        case DefFieldType::DT_IMAGE:
            aSucceed = DefReadFromCacheImage(theReadPtr, (Image**)aDest);
            break;
        case DefFieldType::DT_FONT:
            aSucceed = DefReadFromCacheFont(theReadPtr, (Font**)aDest);
            break;
        case DefFieldType::DT_TRACK_FLOAT:
            aSucceed = DefReadFromCacheFloatTrack(theReadPtr, (FloatParameterTrack*)aDest);
            break;
        }

        if (!aSucceed)
            return false;
    }
    return true;
}

uint DefinitionCalcHashSymbolMap(int aSchemaHash, DefSymbol* theSymbolMap)
{
    while (theSymbolMap->mSymbolName != nullptr)
    {
        aSchemaHash = crc32(aSchemaHash, (const Bytef*)theSymbolMap->mSymbolName, strlen(theSymbolMap->mSymbolName));
        aSchemaHash = crc32(aSchemaHash, (const Bytef*)&theSymbolMap->mSymbolValue, sizeof(int));
        theSymbolMap++;
    }
    return aSchemaHash;
}

uint DefinitionCalcHashDefMap(int aSchemaHash, DefMap* theDefMap, TodList<DefMap*>& theProgressMaps)
{
    for (TodListNode<DefMap*>* aNode = theProgressMaps.mHead; aNode != nullptr; aNode = aNode->mNext)
        if (aNode->mValue == theDefMap)
            return aSchemaHash;
    theProgressMaps.AddTail(theDefMap);

    aSchemaHash = crc32(aSchemaHash, (Bytef*)&theDefMap->mDefSize, sizeof(int));
    for (DefField* aField = theDefMap->mMapFields; *aField->mFieldName != '\0'; aField++)
    {
        aSchemaHash = crc32(aSchemaHash, (Bytef*)&aField->mFieldType, sizeof(DefFieldType));
        aSchemaHash = crc32(aSchemaHash, (Bytef*)&aField->mFieldOffset, sizeof(int));
        switch (aField->mFieldType)
        {
        case DefFieldType::DT_ENUM:
        case DefFieldType::DT_FLAGS:
            aSchemaHash = DefinitionCalcHashSymbolMap(aSchemaHash, (DefSymbol*)aField->mExtraData);
            break;
        case DefFieldType::DT_ARRAY:
            aSchemaHash = DefinitionCalcHashDefMap(aSchemaHash, (DefMap*)aField->mExtraData, theProgressMaps);
            break;
        }
    }
    return aSchemaHash;
}

uint DefinitionCalcHash(DefMap* theDefMap)
{
    TodList<DefMap*> aProgressMaps;
    uint aResult = DefinitionCalcHashDefMap(crc32(0L, (Bytef*)Z_NULL, NULL) + 1, theDefMap, aProgressMaps);
    aProgressMaps.RemoveAll();
    return aResult;
}

void* DefinitionUncompressCompiledBuffer(void* theCompressedBuffer, size_t theCompressedBufferSize, size_t& theUncompressedSize, const SexyString& theCompiledFilePath)
{
    auto sz=theCompressedBufferSize;
    if (theCompressedBufferSize < 8)
    {
        TodTrace("Compile def too small", theCompiledFilePath.c_str());
        return nullptr;
    }
    CompressedDefinitionHeader* aHeader = (CompressedDefinitionHeader*)theCompressedBuffer;
    if (aHeader->mCookie != 0xDEADFED4L)
    {
        TodTrace("Compiled fire cookie wrong: %s\n", theCompiledFilePath.c_str());
        return nullptr;
    }
    Bytef* aUncompressedBuffer = (Bytef*)DefinitionAlloc(aHeader->mUncompressedSize);
    theCompressedBufferSize=aHeader->mUncompressedSize; //my addition
    Bytef* aSrc = (Bytef*)((int)theCompressedBuffer + sizeof(CompressedDefinitionHeader));  
    int aResult = uncompress(aUncompressedBuffer, (uLongf*)&theCompressedBufferSize, aSrc, sz - sizeof(CompressedDefinitionHeader));
    TOD_ASSERT(aResult == Z_OK);
    TOD_ASSERT(theCompressedBufferSize == aHeader->mUncompressedSize);
    theUncompressedSize = aHeader->mUncompressedSize;
    return aUncompressedBuffer;
}

bool DefinitionReadCompiledFile(const SexyString& theCompiledFilePath, DefMap* theDefMap, void* theDefinition)
{
    PerfTimer aTimer;
    aTimer.Start();
    PFILE* pFile = p_fopen(theCompiledFilePath.c_str(), _S("rb"));
    if (pFile)
    {
        p_fseek(pFile, 0, 2);  // Move the pointer to the read location to the end of the file
        size_t aCompressedSize = p_ftell(pFile);  // The offset obtained at this time is the size of the entire file
        p_fseek(pFile, 0, 0);  // Then move the pointer to the read position back to the beginning of the file
        void* aCompressedBuffer = DefinitionAlloc(aCompressedSize);
        // Read the file, and determine whether the actual read size is the complete file size, if it is not equal, it is determined that the read failed
        bool aReadCompressedFailed = p_fread(aCompressedBuffer, sizeof(char), aCompressedSize, pFile) != aCompressedSize;
        p_fclose(pFile);  // Close the resource file stream and free up the memory occupied by pFile
        if (aReadCompressedFailed)  // Determine whether the reading is successful
        {
            TodTrace(_S("Failed to read compiled file: %s\n"), theCompiledFilePath.c_str());
            delete[] aCompressedBuffer;
        }
        else
        {
            size_t aUncompressedSize;
            void* aUncompressedBuffer = DefinitionUncompressCompiledBuffer(aCompressedBuffer, aCompressedSize, aUncompressedSize, theCompiledFilePath);
            delete[] aCompressedBuffer;
            if (aUncompressedBuffer)
            {
                uint aDefHash = DefinitionCalcHash(theDefMap);  // Calculate the CRC check value, which will be used to detect the integrity of the data
                if (aUncompressedSize < theDefMap->mDefSize + sizeof(uint))  // Detect whether the length of the decompressed data is sufficient for the length of "define data + a check value to record data"
                    TodTrace(_S("Compiled file size too small: %s\n"), theCompiledFilePath.c_str());
                else
                {
                    // A pointer to copy a copy of the decompressed data is used to move when reading, and the original pointer will be used to calculate the size of the read area and delete[] operations in the future.
                    void* aBufferPtr = aUncompressedBuffer;
                    uint aCashHash;
                    SMemR(aBufferPtr, &aCashHash, sizeof(uint));  //Read the CRC check value of the record
                    if (aCashHash != aDefHash)  // Determine whether the check value is consistent, if it is inconsistent, the data is wrong
                        TodTrace(_S("Compiled file schema wrong: %s\n"), theCompiledFilePath.c_str());
                    else
                    {
                        // ☆ Officially started reading definition data ☆
                        // Roughly read the definition data of the original type of theDefinition for the first time, and gulp all the recorded data into theDefinition.
                        // At this time, all the data of theDefinition's original non-pointer type will be read correctly, but the variables of its pointer type will be read and assigned as wild pointers.
                        // / The problem of these wild pointers will be fixed in DefMapReadFromCache() with the help of the corresponding DEFIELD's MEXTRDATA in the future
                        SMemR(aBufferPtr, theDefinition, theDefMap->mDefSize);
                        // Repair the wild pointer and flag data, and save the result of whether it is successful, and use it as the return value later
                        bool aResult = DefMapReadFromCache(aBufferPtr, theDefMap, theDefinition);
                        size_t aReadMemSize = (uint)aBufferPtr - (uint)aUncompressedBuffer;
                        delete[] aUncompressedBuffer;
                        if (aResult && aReadMemSize != aUncompressedSize)
                            TodTrace(_S("Compiled file wrong size: %s\n"), theCompiledFilePath.c_str());
                        return aResult;
                    }
                }
            }
            delete[] aUncompressedBuffer;
        }
    }
    return false;
}

SexyString DefinitionGetCompiledFilePathFromXMLFilePath(const SexyString& theXMLFilePath)
{
    return _S("compiled\\") + theXMLFilePath + _S(".compiled");
}

bool IsFileInPakFile(const SexyString& theFilePath)
{
    PFILE* pFile = p_fopen(theFilePath.c_str(), _S("rb"));
    bool aIsInPak = pFile && !pFile->mFP;  
    if (pFile)
    {
        p_fclose(pFile);
    }
    return aIsInPak;
}

bool DefinitionIsCompiled(const SexyString& theXMLFilePath)
{
    SexyString aCompiledFilePath = DefinitionGetCompiledFilePathFromXMLFilePath(theXMLFilePath);
    if (IsFileInPakFile(aCompiledFilePath))
        return true;

    _WIN32_FILE_ATTRIBUTE_DATA lpFileData;
    _FILETIME aCompiledFileTime;
    bool aSucceed = GetFileAttributesEx(aCompiledFilePath.c_str(), _GET_FILEEX_INFO_LEVELS::GetFileExInfoStandard, &lpFileData);
    if (aSucceed)
        aCompiledFileTime = lpFileData.ftLastWriteTime;
    
    if (!GetFileAttributesEx(theXMLFilePath.c_str(), _GET_FILEEX_INFO_LEVELS::GetFileExInfoStandard, &lpFileData))
    {
        TodTrace(_S("Can't file source file to compile '%s'"), theXMLFilePath);
        return true;
    }
    else
        return aSucceed && CompareFileTime(&aCompiledFileTime, &lpFileData.ftLastWriteTime) == 1;
}

void DefinitionFillWithDefaults(DefMap* theDefMap, void* theDefinition)
{
    memset(theDefinition, NULL, theDefMap->mDefSize);  
    for (DefField* aField = theDefMap->mMapFields; *aField->mFieldName != '\0'; aField++)  
        if (aField->mFieldType == DefFieldType::DT_STRING)
            *(char**)((uint)theDefinition + aField->mFieldOffset) = "";  
}

void DefinitionXmlError(XMLParser* theXmlParser, const char* theFormat, ...)
{
    va_list argList;
    va_start(argList, theFormat);
    std::string aFormattedMessage = SexyStringToString(vformat(theFormat, argList));
    va_end(argList);

    int aLine = theXmlParser->GetCurrentLineNum();
    std::string aFileName = theXmlParser->GetFileName();
    TodTraceAndLog("%s(%d): XML Definition Error: %s\n", aFileName.c_str(), aLine, aFormattedMessage.c_str());
}

bool DefinitionReadXMLString(XMLParser* theXmlParser, SexyString& theValue)
{
    XMLElement aXMLElement;
    if (!theXmlParser->NextElement(&aXMLElement))  
    {
        DefinitionXmlError(theXmlParser, "Missing element value");
        return false;
    }
    if (aXMLElement.mType == XMLElement::TYPE_END)  
        return true;
    else if (aXMLElement.mType != XMLElement::TYPE_ELEMENT)  
    {
        DefinitionXmlError(theXmlParser, "unknown element type");
        return false;
    }

    theValue = aXMLElement.mValue;  

    if (!theXmlParser->NextElement(&aXMLElement))  
    {
        DefinitionXmlError(theXmlParser, "Can't read element end");
        return false;
    }
    if (aXMLElement.mType != XMLElement::TYPE_END)  
    {
        DefinitionXmlError(theXmlParser, "Missing element end");
        return false;
    }
    return true;
}

bool DefSymbolValueFromString(DefSymbol* theSymbolMap, const char* theName, int* theResultValue)
{
    while (theSymbolMap->mSymbolName != nullptr)
    {
        if (stricmp(theName, theSymbolMap->mSymbolName) == 0)
        {
            *theResultValue = theSymbolMap->mSymbolValue;
            return true;
        }
        theSymbolMap++;
    }
    return false;
}

bool DefinitionReadIntField(XMLParser* theXmlParser, int* theValue)
{
    SexyString aStringValue;
    if (!DefinitionReadXMLString(theXmlParser, aStringValue))
        return false;

    if (sexysscanf(aStringValue.c_str(), _S("%d"), theValue) == 1)
        return true;

    DefinitionXmlError(theXmlParser, "Can't parse int value '%s'", aStringValue.c_str());
    return false;
}

bool DefinitionReadFloatField(XMLParser* theXmlParser, float* theValue)
{
    SexyString aStringValue;
    if (!DefinitionReadXMLString(theXmlParser, aStringValue))
        return false;

    if (sexysscanf(aStringValue.c_str(), _S("%f"), theValue) == 1)
        return true;

    DefinitionXmlError(theXmlParser, "Can't parse float value '%s'", aStringValue.c_str());
    return false;
}

bool DefinitionReadStringField(XMLParser* theXmlParser, char** theValue)
{
    SexyString aStringValue;
    if (!DefinitionReadXMLString(theXmlParser, aStringValue))
        return false;

    if (aStringValue.size() == 0)
    {
        *theValue = "";
    }
    else
    {
        *theValue = (char*)DefinitionAlloc(aStringValue.size());
        strcpy(*theValue, aStringValue.c_str());
    }
    return true;
}

bool DefinitionReadEnumField(XMLParser* theXmlParser, int* theValue, DefSymbol* theSymbolMap)
{
    SexyString aStringValue;
    if (!DefinitionReadXMLString(theXmlParser, aStringValue))
        return false;

    if (DefSymbolValueFromString(theSymbolMap, aStringValue.c_str(), theValue))
        return true;

    DefinitionXmlError(theXmlParser, "Can't parse enum value '%s'", aStringValue.c_str());
    return false;
}

bool DefinitionReadVector2Field(XMLParser* theXmlParser, SexyVector2* theValue)
{
    SexyString aStringValue;
    if (!DefinitionReadXMLString(theXmlParser, aStringValue))
        return false;

    if (sexysscanf(aStringValue.c_str(), _S("%f %f"), theValue) == 1)
        return true;

    DefinitionXmlError(theXmlParser, "Can't parse vector2 value '%s'", aStringValue.c_str());
    return false;
}

bool DefinitionReadArrayField(XMLParser* theXmlParser, DefinitionArrayDef* theArray, DefField* theField)
{
    DefMap* aDefMap = (DefMap*)theField->mExtraData;

    if (theArray->mArrayCount == 0)
    {
        theArray->mArrayCount = 1;
        theArray->mArrayData = DefinitionAlloc(aDefMap->mDefSize);
    }
    else
    {
        if (theArray->mArrayCount >= 1 && (theArray->mArrayCount == 1 || (theArray->mArrayCount & (theArray->mArrayCount - 1) == 0)))
        {
            void* anOldData = theArray->mArrayData;
            theArray->mArrayData = DefinitionAlloc(2 * theArray->mArrayCount * aDefMap->mDefSize);
            memcpy(theArray->mArrayData, anOldData, theArray->mArrayCount * aDefMap->mDefSize);
            delete[] anOldData;
        }
        theArray->mArrayCount++;
    }

    if (DefinitionLoadMap(theXmlParser, aDefMap, (unsigned char*)theArray->mArrayData + aDefMap->mDefSize * (theArray->mArrayCount - 1)))
        return true;

    DefinitionXmlError(theXmlParser, "failed to read sub def");
    return false;
}

bool DefinitionReadFloatTrackField(XMLParser* theXmlParser, FloatParameterTrack* theTrack)
{
    /*
    ####################################################################################################
    ####################################################################################################
    ####################################################################################################
    ####################################################################################################
    ####################################################################################################
    ####################################################################################################
    ####################################################################################################
    ####################################################################################################
    ####################################################################################################
    ####################################################################################################
    */
    return true;
}

bool DefinitionReadFlagField(XMLParser* theXmlParser, const SexyString& theElementName, uint* theResultValue, DefSymbol* theSymbolMap)
{
    int aValue;
    if (!DefSymbolValueFromString(theSymbolMap, theElementName.c_str(), &aValue))
        return false;

    SexyString aStringValue;
    if (!DefinitionReadXMLString(theXmlParser, aStringValue))
        return false;

    int aFlag;
    if (sexysscanf(aStringValue.c_str(), _S("%f %f"), &aFlag) != 1)
    {
        DefinitionXmlError(theXmlParser, "Can't parse int value '%s'", aStringValue.c_str());
        return false;
    }

    if (aFlag)
    {
        *theResultValue |= 1 << aValue;
    }
    else
    {
        *theResultValue &= ~(1 << aValue);
    }
    return true;
}

bool DefinitionReadImageField(XMLParser* theXmlParser, Image** theImage)
{
    SexyString aStringValue;
    if (!DefinitionReadXMLString(theXmlParser, aStringValue))
        return false;

    if (DefinitionLoadImage(theImage, aStringValue))
        return true;

    std::string aMessgae = StrFormat("Failed to find image '%s' in %s", SexyStringToStringFast(aStringValue).c_str(), theXmlParser->GetFileName());
    TodErrorMessageBox(aMessgae.c_str(), "Missing image");
}

bool DefinitionReadFontField(XMLParser* theXmlParser, Font** theFont)
{
    SexyString aStringValue;
    if (!DefinitionReadXMLString(theXmlParser, aStringValue))
        return false;

    if (DefinitionLoadFont(theFont, aStringValue))
        return true;

    std::string aMessgae = StrFormat("Failed to find font '%s' in %s", SexyStringToStringFast(aStringValue).c_str(), theXmlParser->GetFileName());
    TodErrorMessageBox(aMessgae.c_str(), "Missing font");
}

bool DefinitionReadField(XMLParser* theXmlParser, DefMap* theDefMap, void* theDefinition, bool* theDone)
{
    if (theXmlParser->HasFailed())
        return false;

    XMLElement aXMLElement;
    if (!theXmlParser->NextElement(&aXMLElement) || aXMLElement.mType == XMLElement::TYPE_END)  
    {
        *theDone = true;  
        return true;
    }
    if (aXMLElement.mType != XMLElement::TYPE_START)  
    {
        DefinitionXmlError(theXmlParser, "Missing element start");
        return false;
    }

    for (DefField* aField = theDefMap->mMapFields; *aField->mFieldName != '\0'; aField++)
    {
        void* pVar = (void*)((uint)theDefinition + aField->mFieldOffset);
        if (aField->mFieldType == DefFieldType::DT_FLAGS && DefinitionReadFlagField(theXmlParser, aXMLElement.mValue, nullptr, (DefSymbol*)aField->mExtraData))
            return true;
        
        if (stricmp(aXMLElement.mValue.c_str(), aField->mFieldName) == 0)  
        {
            bool aSuccess;
            switch (aField->mFieldType)
            {
            case DefFieldType::DT_INT:
                aSuccess = DefinitionReadIntField(theXmlParser, (int*)pVar);
                break;
            case DefFieldType::DT_FLOAT:
                aSuccess = DefinitionReadFloatField(theXmlParser, (float*)pVar);
                break;
            case DefFieldType::DT_STRING:
                aSuccess = DefinitionReadStringField(theXmlParser, (char**)pVar);
                break;
            case DefFieldType::DT_ENUM:
                aSuccess = DefinitionReadEnumField(theXmlParser, (int*)pVar, (DefSymbol*)aField->mExtraData);
                break;
            case DefFieldType::DT_VECTOR2:
                aSuccess = DefinitionReadVector2Field(theXmlParser, (SexyVector2*)pVar);
                break;
            case DefFieldType::DT_ARRAY:
                aSuccess = DefinitionReadArrayField(theXmlParser, (DefinitionArrayDef*)pVar, aField);
                break;
            case DefFieldType::DT_TRACK_FLOAT:
                aSuccess = DefinitionReadFloatTrackField(theXmlParser, (FloatParameterTrack*)pVar);
                break;
            case DefFieldType::DT_IMAGE:
                aSuccess = DefinitionReadImageField(theXmlParser, (Image**)pVar);
                break;
            case DefFieldType::DT_FONT:
                aSuccess = DefinitionReadFontField(theXmlParser, (Font**)pVar);
                break;
            default:
                TOD_ASSERT(false);
                break;
            }
            if (aSuccess)
                return true;

            DefinitionXmlError(theXmlParser, "Failed to read '%s' field", aXMLElement.mValue.c_str());
            return false;
        }
    }
    DefinitionXmlError(theXmlParser, "Ignoring unknown element '%s'", aXMLElement.mValue.c_str());  
    return false;
}

bool DefinitionLoadMap(XMLParser* theXmlParser, DefMap* theDefMap, void* theDefinition)
{
    if (theDefMap->mConstructorFunc)
        theDefMap->mConstructorFunc(theDefinition);  
    else
        DefinitionFillWithDefaults(theDefMap, theDefinition);  

    bool aDone = false;
    while (!aDone)
        if (!DefinitionReadField(theXmlParser, theDefMap, theDefinition, &aDone))
            return false;
    return true;
}

bool DefinitionWriteCompiledFile(const SexyString& theCompiledFilePath, DefMap* theDefMap, void* theDefinition)
{
    /*
    ####################################################################################################
    ####################################################################################################
    ####################################################################################################
    ####################################################################################################
    ####################################################################################################
    ####################################################################################################
    ####################################################################################################
    ####################################################################################################
    ####################################################################################################
    ####################################################################################################
    */
    return true;
}

bool DefinitionCompileFile(const SexyString theXMLFilePath, const SexyString& theCompiledFilePath, DefMap* theDefMap, void* theDefinition)
{
    XMLParser aXMLParser;
    if (!aXMLParser.OpenFile(theXMLFilePath))
    {
        TodTrace(_S("XML file not found: %s\n"), theXMLFilePath.c_str());
        return false;
    }
    else if (!DefinitionLoadMap(&aXMLParser, theDefMap, theDefinition))
        return false;
    
    DefinitionWriteCompiledFile(theCompiledFilePath, theDefMap, theDefinition);
    return true;
}

bool DefinitionCompileAndLoad(const SexyString& theXMLFilePath, DefMap* theDefMap, void* theDefinition)
{
    //Changed to compile from in debug to this preprocessor
#ifdef _COMPILEXML  

    TodHesitationTrace(_S("predef"));
    SexyString aCompiledFilePath = DefinitionGetCompiledFilePathFromXMLFilePath(theXMLFilePath);
    if (DefinitionIsCompiled(theXMLFilePath) && DefinitionReadCompiledFile(aCompiledFilePath, theDefMap, theDefinition))
    {
        TodHesitationTrace(_S("loaded %s"), aCompiledFilePath.c_str());
        return true;
    }
    else
    {
        PerfTimer aTimer;
        aTimer.Start();
        bool aResult = DefinitionCompileFile(theXMLFilePath, aCompiledFilePath, theDefMap, theDefinition);
        TodTrace(_S("compile %d ms:'%s'"), (int)aTimer.GetDuration(), aCompiledFilePath.c_str());
        TodHesitationTrace(_S("compiled %s"), aCompiledFilePath.c_str());
        return aResult;
    }

#else  

    SexyString aCompiledFilePath = DefinitionGetCompiledFilePathFromXMLFilePath(theXMLFilePath);
    if (DefinitionReadCompiledFile(aCompiledFilePath, theDefMap, theDefinition))
        return true;

    TodErrorMessageBox(StrFormat(_S("missing resource %s"), aCompiledFilePath.c_str()).c_str(), _S("Error"));
    exit(0);
    
#endif
}

float FloatTrackEvaluate(FloatParameterTrack& theTrack, float theTimeValue, float theInterp)
{
    if (theTrack.mCountNodes == 0)
        return 0.0f;

    if (theTimeValue < theTrack.mNodes[0].mTime)  
        return TodCurveEvaluate(theInterp, theTrack.mNodes[0].mLowValue, theTrack.mNodes[0].mHighValue, theTrack.mNodes[0].mDistribution);

    for (int i = 1; i < theTrack.mCountNodes; i++)
    {
        FloatParameterTrackNode* aNodeNxt = &theTrack.mNodes[i];
        if (theTimeValue <= aNodeNxt->mTime)  
        {
            FloatParameterTrackNode* aNodeCur = &theTrack.mNodes[i - 1];
            float aTimeFraction = (theTimeValue - aNodeCur->mTime) / (aNodeNxt->mTime - aNodeCur->mTime);
            float aLeftValue = TodCurveEvaluate(theInterp, aNodeCur->mLowValue, aNodeCur->mHighValue, aNodeCur->mDistribution);
            float aRightValue = TodCurveEvaluate(theInterp, aNodeNxt->mLowValue, aNodeNxt->mHighValue, aNodeNxt->mDistribution);
            return TodCurveEvaluate(aTimeFraction, aLeftValue, aRightValue, aNodeCur->mCurveType);
        }
    }

    FloatParameterTrackNode* aLastNode = &theTrack.mNodes[theTrack.mCountNodes - 1];  
    return TodCurveEvaluate(theInterp, aLastNode->mLowValue, aLastNode->mHighValue, aLastNode->mDistribution);
}

void FloatTrackSetDefault(FloatParameterTrack& theTrack, float theValue)
{
    if (theTrack.mNodes == nullptr && theValue != 0.0f)  
    {
        theTrack.mCountNodes = 1;  
        FloatParameterTrackNode* aNode = (FloatParameterTrackNode*)DefinitionAlloc(sizeof(FloatParameterTrackNode));
        theTrack.mNodes = aNode;
        aNode->mTime = 0.0f;
        aNode->mLowValue = theValue;
        aNode->mHighValue = theValue;
        aNode->mCurveType = TodCurves::CURVE_CONSTANT;
        aNode->mDistribution = TodCurves::CURVE_LINEAR;
    }
}

bool FloatTrackIsSet(const FloatParameterTrack& theTrack)
{
	return theTrack.mCountNodes != 0 && theTrack.mNodes[0].mCurveType != TodCurves::CURVE_CONSTANT;
}

bool FloatTrackIsConstantZero(FloatParameterTrack& theTrack)
{
    return theTrack.mCountNodes == 0 || (theTrack.mCountNodes == 1 && theTrack.mNodes[0].mLowValue == 0.0f && theTrack.mNodes[0].mHighValue == 0.0f);
}

float FloatTrackEvaluateFromLastTime(FloatParameterTrack& theTrack, float theTimeValue, float theInterp)
{
    return theTimeValue < 0.0f ? 0.0f : FloatTrackEvaluate(theTrack, theTimeValue, theInterp);
}

void DefinitionFreeArrayField(DefinitionArrayDef* theArray, DefMap* theDefMap)
{
    for (int i = 0; i < theArray->mArrayCount; i++)
        DefinitionFreeMap(theDefMap, (void*)((int)theArray->mArrayData + theDefMap->mDefSize * i));  
    delete[] theArray->mArrayData;
    theArray->mArrayData = nullptr;
}

void DefinitionFreeMap(DefMap* theDefMap, void* theDefinition)
{
    for (DefField* aField = theDefMap->mMapFields; *aField->mFieldName != '\0'; aField++)
    {
        void* aVar = (void*)((int)theDefinition + aField->mFieldOffset);  
        switch (aField->mFieldType)
        {
        case DefFieldType::DT_STRING:
            if (**(char**)aVar != '\0')
                delete[] *(char**)aVar;  
            *(char**)aVar = nullptr;
            break;
        case DefFieldType::DT_ARRAY:
            DefinitionFreeArrayField((DefinitionArrayDef*)aVar, (DefMap*)aField->mExtraData);
            break;
        case DefFieldType::DT_TRACK_FLOAT:
            if (((FloatParameterTrack*)aVar)->mCountNodes != 0)
                delete[]((FloatParameterTrack*)aVar)->mNodes;  
            ((FloatParameterTrack*)aVar)->mNodes = nullptr;
            break;
        }
    }
}