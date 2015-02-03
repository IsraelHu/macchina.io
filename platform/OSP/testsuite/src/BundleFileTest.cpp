//
// BundleFileTest.cpp
//
// $Id: //poco/1.4/OSP/testsuite/src/BundleFileTest.cpp#2 $
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "BundleFileTest.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "Poco/OSP/BundleFile.h"
#include "Poco/File.h"
#include "Poco/Path.h"
#include "Poco/Exception.h"
#include <fstream>
#include <memory>


using Poco::OSP::BundleFile;
using Poco::OSP::BundleStorage;
using Poco::File;


BundleFileTest::BundleFileTest(const std::string& name): CppUnit::TestCase(name)
{
}


BundleFileTest::~BundleFileTest()
{
}


void BundleFileTest::testResource()
{
	std::string s;
	BundleStorage::Ptr pBF(new BundleFile("testBundle.zip"));
	
	std::auto_ptr<std::istream> istr1(pBF->getResource("META-INF/manifest.mf"));
	assert (istr1.get() != 0);
	std::getline(*istr1, s);
	assert (s == "Manifest-Version: 1.0");
	
	std::auto_ptr<std::istream> istr2(pBF->getResource("bundle.properties"));
	assert (istr2.get() != 0);
	std::getline(*istr2, s);
	assert (s == "foo: bar");
	
	std::istream* istr3(pBF->getResource("nonexistent"));
	assert (istr3 == 0);
}


void BundleFileTest::testDirectory()
{
	BundleStorage::Ptr pBF(new BundleFile("testBundle.zip"));
	std::vector<std::string> files;
	pBF->list("", files);
	assert (files.size() == 2);
	
	pBF->list("META-INF", files);
	assert (files.size() == 1);
	assert (files[0] == "manifest.mf");
}


void BundleFileTest::setUp()
{
	// The following is a ZIP file containing the same
	// directory hierarchy as is used in BundleDirectoryTest.
	static const unsigned char TEST_BUNDLE_ZIP[] = 
	{
		0x50, 0x4b, 0x03, 0x04, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x76, 0x83, 0x36, 0xe8, 0x16,
		0xfa, 0x93, 0x0a, 0x00, 0x00, 0x00, 0x0a, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00, 0x62, 0x75,
		0x6e, 0x64, 0x6c, 0x65, 0x2e, 0x70, 0x72, 0x6f, 0x70, 0x65, 0x72, 0x74, 0x69, 0x65, 0x73, 0x66,
		0x6f, 0x6f, 0x3a, 0x20, 0x62, 0x61, 0x72, 0x0a, 0x0a, 0x50, 0x4b, 0x03, 0x04, 0x0a, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x11, 0x76, 0x83, 0x36, 0x7a, 0xdf, 0x5a, 0x20, 0x16, 0x00, 0x00, 0x00, 0x16,
		0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x4d, 0x45, 0x54, 0x41, 0x2d, 0x49, 0x4e, 0x46, 0x2f,
		0x6d, 0x61, 0x6e, 0x69, 0x66, 0x65, 0x73, 0x74, 0x2e, 0x6d, 0x66, 0x4d, 0x61, 0x6e, 0x69, 0x66,
		0x65, 0x73, 0x74, 0x2d, 0x56, 0x65, 0x72, 0x73, 0x69, 0x6f, 0x6e, 0x3a, 0x20, 0x31, 0x2e, 0x30,
		0x0a, 0x50, 0x4b, 0x03, 0x04, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x76, 0x83, 0x36, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x4d,
		0x45, 0x54, 0x41, 0x2d, 0x49, 0x4e, 0x46, 0x2f, 0x50, 0x4b, 0x01, 0x02, 0x14, 0x00, 0x0a, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x11, 0x76, 0x83, 0x36, 0xe8, 0x16, 0xfa, 0x93, 0x0a, 0x00, 0x00, 0x00,
		0x0a, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x20, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x62, 0x75, 0x6e, 0x64, 0x6c, 0x65, 0x2e, 0x70, 0x72, 0x6f,
		0x70, 0x65, 0x72, 0x74, 0x69, 0x65, 0x73, 0x50, 0x4b, 0x01, 0x02, 0x14, 0x00, 0x0a, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x11, 0x76, 0x83, 0x36, 0x7a, 0xdf, 0x5a, 0x20, 0x16, 0x00, 0x00, 0x00, 0x16,
		0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x20, 0x00, 0x00,
		0x00, 0x39, 0x00, 0x00, 0x00, 0x4d, 0x45, 0x54, 0x41, 0x2d, 0x49, 0x4e, 0x46, 0x2f, 0x6d, 0x61,
		0x6e, 0x69, 0x66, 0x65, 0x73, 0x74, 0x2e, 0x6d, 0x66, 0x50, 0x4b, 0x01, 0x02, 0x14, 0x00, 0x0a,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x76, 0x83, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10,
		0x00, 0x00, 0x00, 0x81, 0x00, 0x00, 0x00, 0x4d, 0x45, 0x54, 0x41, 0x2d, 0x49, 0x4e, 0x46, 0x2f,
		0x50, 0x4b, 0x05, 0x06, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x03, 0x00, 0xb8, 0x00, 0x00, 0x00,
		0xa8, 0x00, 0x00, 0x00, 0x00, 0x00
	};

	std::ofstream ostr("testBundle.zip", std::ios::binary);
	ostr.write(reinterpret_cast<const char*>(&TEST_BUNDLE_ZIP[0]), sizeof(TEST_BUNDLE_ZIP));
}


void BundleFileTest::tearDown()
{
	File f("testBundle.zip");
	if (f.exists())
	{
		f.remove(true);
	}
}


CppUnit::Test* BundleFileTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("BundleFileTest");

	CppUnit_addTest(pSuite, BundleFileTest, testResource);
	CppUnit_addTest(pSuite, BundleFileTest, testDirectory);

	return pSuite;
}
