DIST_SUBDIRS = secp256k1 univalue

AM_LDFLAGS = $(PTHREAD_CFLAGS) $(LIBTOOL_LDFLAGS) $(HARDENED_LDFLAGS)
AM_CXXFLAGS = $(HARDENED_CXXFLAGS)
AM_CPPFLAGS = $(HARDENED_CPPFLAGS)
EXTRA_LIBRARIES =

if EMBEDDED_UNIVALUE
LIBUNIVALUE = univalue/libunivalue.la

$(LIBUNIVALUE): $(wildcard univalue/lib/*) $(wildcard univalue/include/*)
	$(AM_V_at)$(MAKE) $(AM_MAKEFLAGS) -C $(@D) $(@F)
else
LIBUNIVALUE = $(UNIVALUE_LIBS)
endif

ELETACOIN_CONFIG_INCLUDES=-I$(builddir)/config
ELETACOIN_INCLUDES=-I$(builddir) -I$(builddir)/obj $(BDB_CPPFLAGS) $(BOOST_CPPFLAGS) $(LEVELDB_CPPFLAGS) $(CRYPTO_CFLAGS) $(SSL_CFLAGS)

ELETACOIN_INCLUDES += -I$(srcdir)/secp256k1/include
ELETACOIN_INCLUDES += $(UNIVALUE_CFLAGS)

LIBELETACOIN_SERVER=libeletacoin_server.a
LIBELETACOIN_COMMON=libeletacoin_common.a
LIBELETACOIN_CONSENSUS=libeletacoin_consensus.a
LIBELETACOIN_CLI=libeletacoin_cli.a
LIBELETACOIN_UTIL=libeletacoin_util.a
LIBELETACOIN_CRYPTO=crypto/libeletacoin_crypto.a
LIBELETACOINQT=qt/libeletacoinqt.a
LIBSECP256K1=secp256k1/libsecp256k1.la

if ENABLE_ZMQ
LIBELETACOIN_ZMQ=libeletacoin_zmq.a
endif
if BUILD_ELETACOIN_LIBS
LIBELETACOINCONSENSUS=libeletacoinconsensus.la
endif
if ENABLE_WALLET
LIBELETACOIN_WALLET=libeletacoin_wallet.a
endif

$(LIBSECP256K1): $(wildcard secp256k1/src/*) $(wildcard secp256k1/include/*)
	$(AM_V_at)$(MAKE) $(AM_MAKEFLAGS) -C $(@D) $(@F)

# Make is not made aware of per-object dependencies to avoid limiting building parallelization
# But to build the less dependent modules first, we manually select their order here:
EXTRA_LIBRARIES += \
  $(LIBELETACOIN_CRYPTO) \
  $(LIBELETACOIN_UTIL) \
  $(LIBELETACOIN_COMMON) \
  $(LIBELETACOIN_CONSENSUS) \
  $(LIBELETACOIN_SERVER) \
  $(LIBELETACOIN_CLI) \
  $(LIBELETACOIN_WALLET) \
  $(LIBELETACOIN_ZMQ)

lib_LTLIBRARIES = $(LIBELETACOINCONSENSUS)

bin_PROGRAMS =
TESTS =
BENCHMARKS =

if BUILD_ELETACOIND
  bin_PROGRAMS += eletacoind
endif

if BUILD_ELETACOIN_UTILS
  bin_PROGRAMS += eletacoin-cli eletacoin-tx
endif

.PHONY: FORCE check-symbols check-security
# eletacoin core #
ELETACOIN_CORE_H = \
  addressindex.h \
  spentindex.h \
  timestampindex.h \
  addrman.h \
  base58.h \
  bignum.h \
  bloom.h \
  blockencodings.h \
  chain.h \
  chainparams.h \
  chainparamsbase.h \
  chainparamsseeds.h \
  checkpoints.h \
  checkqueue.h \
  clientversion.h \
  coincontrol.h \
  coins.h \
  compat.h \
  compat/byteswap.h \
  compat/endian.h \
  compat/sanity.h \
  compressor.h \
  consensus/consensus.h \
  core_io.h \
  core_memusage.h \
  httprpc.h \
  httpserver.h \
  indirectmap.h \
  kernel.h \
  init.h \
  key.h \
  keystore.h \
  dbwrapper.h \
  limitedmap.h \
  main.h \
  memusage.h \
  merkleblock.h \
  miner.h \
  net.h \
  netbase.h \
  noui.h \
  policy/fees.h \
  policy/policy.h \
  policy/rbf.h \
	pow.h \
  pos.h \
  consensus/cfund.h \
  protocol.h \
  random.h \
  reverselock.h \
  rpc/client.h \
  rpc/protocol.h \
  rpc/server.h \
  rpc/register.h \
  scheduler.h \
  script/sigcache.h \
  script/sign.h \
  script/standard.h \
  script/ismine.h \
  streams.h \
  support/allocators/secure.h \
  support/allocators/zeroafterfree.h \
  support/cleanse.h \
  support/pagelocker.h \
  sync.h \
  threadsafety.h \
  timedata.h \
  torcontrol.h \
  txdb.h \
  txmempool.h \
  ui_interface.h \
  undo.h \
  util.h \
  utilmoneystr.h \
  utils/dns_utils.h \
  utiltime.h \
  validationinterface.h \
  versionbits.h \
  wallet/crypter.h \
  wallet/db.h \
  wallet/eletatech.h \
  wallet/rpcwallet.h \
  wallet/wallet.h \
  wallet/walletdb.h \
  zmq/zmqabstractnotifier.h \
  zmq/zmqconfig.h\
  zmq/zmqnotificationinterface.h \
  zmq/zmqpublishnotifier.h


obj/build.h: FORCE
	@$(MKDIR_P) $(builddir)/obj
	@$(top_srcdir)/share/genbuild.sh $(abs_top_builddir)/src/obj/build.h \
	  $(abs_top_srcdir)
libeletacoin_util_a-clientversion.$(OBJEXT): obj/build.h

# server: shared between eletacoind and eletacoin-qt
libeletacoin_server_a_CPPFLAGS = $(AM_CPPFLAGS) $(ELETACOIN_INCLUDES) $(MINIUPNPC_CPPFLAGS) $(EVENT_CFLAGS) $(EVENT_PTHREADS_CFLAGS)
libeletacoin_server_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libeletacoin_server_a_SOURCES = \
  addrman.cpp \
  bloom.cpp \
  blockencodings.cpp \
  chain.cpp \
  checkpoints.cpp \
  consensus/cfund.cpp \
  httprpc.cpp \
  httpserver.cpp \
  kernel.cpp \
  init.cpp \
  dbwrapper.cpp \
  main.cpp \
  merkleblock.cpp \
  miner.cpp \
  net.cpp \
  noui.cpp \
  policy/fees.cpp \
  policy/policy.cpp \
  pow.cpp \
  pos.cpp \
  rest.cpp \
  rpc/blockchain.cpp \
  rpc/mining.cpp \
  rpc/misc.cpp \
  rpc/net.cpp \
  rpc/rawtransaction.cpp \
  rpc/server.cpp \
  script/sigcache.cpp \
  script/ismine.cpp \
  timedata.cpp \
  torcontrol.cpp \
  txdb.cpp \
  txmempool.cpp \
  ui_interface.cpp \
  utils/dns_utils.cpp \
  validationinterface.cpp \
  versionbits.cpp \
  $(ELETACOIN_CORE_H)

if ENABLE_ZMQ
libeletacoin_zmq_a_CPPFLAGS = $(ELETACOIN_INCLUDES) $(ZMQ_CFLAGS)
libeletacoin_zmq_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libeletacoin_zmq_a_SOURCES = \
  zmq/zmqabstractnotifier.cpp \
  zmq/zmqnotificationinterface.cpp \
  zmq/zmqpublishnotifier.cpp
endif


# wallet: shared between eletacoind and eletacoin-qt, but only linked
# when wallet enabled
libeletacoin_wallet_a_CPPFLAGS = $(AM_CPPFLAGS) $(ELETACOIN_INCLUDES)
libeletacoin_wallet_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libeletacoin_wallet_a_SOURCES = \
  consensus/cfund.cpp \
  wallet/crypter.cpp \
  wallet/db.cpp \
  wallet/eletatech.cpp \
  wallet/rpcdump.cpp \
  wallet/rpcwallet.cpp \
  wallet/wallet.cpp \
  wallet/walletdb.cpp \
  policy/rbf.cpp \
  $(ELETACOIN_CORE_H)

# crypto primitives library
crypto_libeletacoin_crypto_a_CPPFLAGS = $(AM_CPPFLAGS) $(ELETACOIN_CONFIG_INCLUDES)
crypto_libeletacoin_crypto_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
crypto_libeletacoin_crypto_a_SOURCES = \
  crypto/aes.cpp \
  crypto/aes.h \
  crypto/common.h \
  crypto/hmac_sha256.cpp \
  crypto/hmac_sha256.h \
  crypto/hmac_sha512.cpp \
  crypto/hmac_sha512.h \
  crypto/ripemd160.cpp \
  crypto/ripemd160.h \
  crypto/sha1.cpp \
  crypto/sha1.h \
  crypto/sha256.cpp \
  crypto/sha256.h \
  crypto/sha512.cpp \
  crypto/sha512.h

# consensus: shared between all executables that validate any consensus rules.
libeletacoin_consensus_a_CPPFLAGS = $(AM_CPPFLAGS) $(ELETACOIN_INCLUDES)
libeletacoin_consensus_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libeletacoin_consensus_a_SOURCES = \
  amount.h \
  arith_uint256.cpp \
  arith_uint256.h \
  consensus/merkle.cpp \
  consensus/merkle.h \
  consensus/params.h \
  consensus/validation.h \
	aes_helper.c \
	blake.c \
	bmw.c \
	cubehash.c \
	echo.c \
	fugue.c \
	groestl.c \
	keccak.c \
	hamsi_helper.c \
	hamsi.c \
	jh.c \
	luffa.c \
	shavite.c \
	simd.c \
	skein.c \
	sph_blake.h \
	sph_bmw.h \
	sph_cubehash.h \
	sph_echo.h \
	sph_fugue.h \
	sph_groestl.h \
	sph_hamsi.h \
	sph_jh.h \
	sph_keccak.h \
	sph_luffa.h \
	sph_shavite.h \
	sph_simd.h \
	sph_skein.h \
	sph_types.h \
	hashblock.h \
  hash.cpp \
  hash.h \
  prevector.h \
  primitives/block.cpp \
  primitives/block.h \
  primitives/transaction.cpp \
  primitives/transaction.h \
  pubkey.cpp \
  pubkey.h \
  script/eletacoinconsensus.cpp \
  script/interpreter.cpp \
  script/interpreter.h \
  script/script.cpp \
  script/script.h \
  script/script_error.cpp \
  script/script_error.h \
  serialize.h \
	tinyformat.h \
  uint256.cpp \
  uint256.h \
  utilstrencodings.cpp \
  utilstrencodings.h \
  version.h


# common: shared between eletacoind, and eletacoin-qt and non-server tools
libeletacoin_common_a_CPPFLAGS = $(AM_CPPFLAGS) $(ELETACOIN_INCLUDES)
libeletacoin_common_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libeletacoin_common_a_SOURCES = \
  amount.cpp \
  base58.cpp \
  chainparams.cpp \
  coins.cpp \
  compressor.cpp \
  core_read.cpp \
  core_write.cpp \
  key.cpp \
  keystore.cpp \
  netbase.cpp \
  protocol.cpp \
  scheduler.cpp \
  script/sign.cpp \
  script/standard.cpp \
  $(ELETACOIN_CORE_H)

# util: shared between all executables.
# This library *must* be included to make sure that the glibc
# backward-compatibility objects and their sanity checks are linked.
libeletacoin_util_a_CPPFLAGS = $(AM_CPPFLAGS) $(ELETACOIN_INCLUDES)
libeletacoin_util_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libeletacoin_util_a_SOURCES = \
  support/pagelocker.cpp \
  chainparamsbase.cpp \
  clientversion.cpp \
  compat/glibc_sanity.cpp \
  compat/glibcxx_sanity.cpp \
  compat/strnlen.cpp \
  random.cpp \
  rpc/protocol.cpp \
  support/cleanse.cpp \
  sync.cpp \
  util.cpp \
  utilmoneystr.cpp \
  utilstrencodings.cpp \
  utiltime.cpp \
  $(ELETACOIN_CORE_H)

if GLIBC_BACK_COMPAT
libeletacoin_util_a_SOURCES += compat/glibc_compat.cpp
endif

# cli: shared between eletacoin-cli and eletacoin-qt
libeletacoin_cli_a_CPPFLAGS = $(AM_CPPFLAGS) $(ELETACOIN_INCLUDES)
libeletacoin_cli_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libeletacoin_cli_a_SOURCES = \
  rpc/client.cpp \
  $(ELETACOIN_CORE_H)

nodist_libeletacoin_util_a_SOURCES = $(srcdir)/obj/build.h
#

# eletacoind binary #
eletacoind_SOURCES = eletacoind.cpp
eletacoind_CPPFLAGS = $(AM_CPPFLAGS) $(ELETACOIN_INCLUDES)
eletacoind_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
eletacoind_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
eletacoind_SOURCES += eletacoind-res.rc
endif

eletacoind_LDADD = \
  $(LIBELETACOIN_SERVER) \
  $(LIBELETACOIN_COMMON) \
  $(LIBUNIVALUE) \
  $(LIBELETACOIN_UTIL) \
  $(LIBELETACOIN_WALLET) \
  $(LIBELETACOIN_ZMQ) \
  $(LIBELETACOIN_CONSENSUS) \
  $(LIBELETACOIN_CRYPTO) \
  $(LIBLEVELDB) \
  $(LIBMEMENV) \
  $(LIBSECP256K1)

eletacoind_LDADD += $(BOOST_LIBS) $(BDB_LIBS) $(SSL_LIBS) $(UNBOUND_LIBS) $(CURL_LIBS) $(CRYPTO_LIBS) $(MINIUPNPC_LIBS) $(EVENT_PTHREADS_LIBS) $(EVENT_LIBS) $(ZMQ_LIBS)

# eletacoin-cli binary #
eletacoin_cli_SOURCES = eletacoin-cli.cpp
eletacoin_cli_CPPFLAGS = $(AM_CPPFLAGS) $(ELETACOIN_INCLUDES) $(EVENT_CFLAGS)
eletacoin_cli_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
eletacoin_cli_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
eletacoin_cli_SOURCES += eletacoin-cli-res.rc
endif

eletacoin_cli_LDADD = \
  $(LIBELETACOIN_CLI) \
  $(LIBUNIVALUE) \
  $(LIBELETACOIN_UTIL) \
  $(LIBELETACOIN_CRYPTO)

eletacoin_cli_LDADD += $(BOOST_LIBS) $(SSL_LIBS) $(UNBOUND_LIBS) $(CURL_LIBS) $(CRYPTO_LIBS) $(EVENT_LIBS)
#

# eletacoin-tx binary #
eletacoin_tx_SOURCES = eletacoin-tx.cpp
eletacoin_tx_CPPFLAGS = $(AM_CPPFLAGS) $(ELETACOIN_INCLUDES)
eletacoin_tx_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
eletacoin_tx_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
eletacoin_tx_SOURCES += eletacoin-tx-res.rc
endif

eletacoin_tx_LDADD = \
  $(LIBUNIVALUE) \
  $(LIBELETACOIN_COMMON) \
  $(LIBELETACOIN_UTIL) \
  $(LIBELETACOIN_CONSENSUS) \
  $(LIBELETACOIN_CRYPTO) \
  $(LIBSECP256K1)

eletacoin_tx_LDADD += $(BOOST_LIBS) $(CRYPTO_LIBS)
#

# eletacoinconsensus library #
if BUILD_ELETACOIN_LIBS
include_HEADERS = script/eletacoinconsensus.h
libeletacoinconsensus_la_SOURCES = $(crypto_libeletacoin_crypto_a_SOURCES) $(libeletacoin_consensus_a_SOURCES)

if GLIBC_BACK_COMPAT
  libeletacoinconsensus_la_SOURCES += compat/glibc_compat.cpp
endif

libeletacoinconsensus_la_LDFLAGS = $(AM_LDFLAGS) -no-undefined $(RELDFLAGS)
libeletacoinconsensus_la_LIBADD = $(LIBSECP256K1)
libeletacoinconsensus_la_CPPFLAGS = $(AM_CPPFLAGS) -I$(builddir)/obj -I$(srcdir)/secp256k1/include -DBUILD_ELETACOIN_INTERNAL
libeletacoinconsensus_la_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)

endif
#

CTAES_DIST =  crypto/ctaes/bench.c
CTAES_DIST += crypto/ctaes/ctaes.c
CTAES_DIST += crypto/ctaes/ctaes.h
CTAES_DIST += crypto/ctaes/README.md
CTAES_DIST += crypto/ctaes/test.c

CLEANFILES = $(EXTRA_LIBRARIES)

CLEANFILES += *.gcda *.gcno
CLEANFILES += compat/*.gcda compat/*.gcno
CLEANFILES += consensus/*.gcda consensus/*.gcno
CLEANFILES += crypto/*.gcda crypto/*.gcno
CLEANFILES += policy/*.gcda policy/*.gcno
CLEANFILES += primitives/*.gcda primitives/*.gcno
CLEANFILES += script/*.gcda script/*.gcno
CLEANFILES += support/*.gcda support/*.gcno
CLEANFILES += univalue/*.gcda univalue/*.gcno
CLEANFILES += wallet/*.gcda wallet/*.gcno
CLEANFILES += wallet/test/*.gcda wallet/test/*.gcno
CLEANFILES += zmq/*.gcda zmq/*.gcno

DISTCLEANFILES = obj/build.h

EXTRA_DIST = $(CTAES_DIST)

clean-local:
	-$(MAKE) -C secp256k1 clean
	-$(MAKE) -C univalue clean
	-rm -f leveldb/*/*.gcda leveldb/*/*.gcno leveldb/helpers/memenv/*.gcda leveldb/helpers/memenv/*.gcno
	-rm -f config.h
	-rm -rf test/__pycache__

.rc.o:
	@test -f $(WINDRES)
	## FIXME: How to get the appropriate modulename_CPPFLAGS in here?
	$(AM_V_GEN) $(WINDRES) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(CPPFLAGS) -DWINDRES_PREPROC -i $< -o $@

.mm.o:
	$(AM_V_CXX) $(OBJCXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) \
	  $(CPPFLAGS) $(AM_CXXFLAGS) $(QT_INCLUDES) $(AM_CXXFLAGS) $(PIE_FLAGS) $(CXXFLAGS) -c -o $@ $<

check-symbols: $(bin_PROGRAMS)
if GLIBC_BACK_COMPAT
	@echo "Checking glibc back compat..."
	$(AM_V_at) READELF=$(READELF) CPPFILT=$(CPPFILT) $(top_srcdir)/contrib/devtools/symbol-check.py < $(bin_PROGRAMS)
endif

check-security: $(bin_PROGRAMS)
if HARDEN
	@echo "Checking binary security..."
	$(AM_V_at) READELF=$(READELF) OBJDUMP=$(OBJDUMP) $(top_srcdir)/contrib/devtools/security-check.py < $(bin_PROGRAMS)
endif

%.pb.cc %.pb.h: %.proto
	@test -f $(PROTOC)
	$(AM_V_GEN) $(PROTOC) --cpp_out=$(@D) --proto_path=$(<D) $<

if EMBEDDED_LEVELDB
include Makefile.leveldb.include
endif

if ENABLE_TESTS
include Makefile.test.include
endif

if ENABLE_BENCH
include Makefile.bench.include
endif

if ENABLE_QT
include Makefile.qt.include
endif

if ENABLE_QT_TESTS
include Makefile.qttest.include
endif
