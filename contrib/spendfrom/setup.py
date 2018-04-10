from distutils.core import setup
setup(name='ELTspendfrom',
      version='1.0',
      description='Command-line utility for eletacoin "coin control"',
      author='Gavin Andresen',
      author_email='gavin@eletacoinfoundation.org',
      requires=['jsonrpc'],
      scripts=['spendfrom.py'],
      )
