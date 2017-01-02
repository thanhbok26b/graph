import random, string, os
from pprint import pprint

class Testcase:
	'''
	    ### GRAPH API UNITEST ###
	@ Input:
		- vertex name pattern
	@ Output:
		- a random set of vertex
		- a random set of edge
	@ Action:
		- save output to file
		- open graph program to run test 
		manually on the set
		- graph visualization
	'''
	def __init__(self):
		self.vertices = []
		self.edges = {}
		self.generate_testcase()

	def generate_testcase(self):
		self.generate_vertices()
		self.generate_edges()
		self.outfile()

	def generate_vertices(self, min_v=5, max_v=10):
		n = random.randint(min_v, max_v)
		self.vertices = ['A%d' % i for i in range(n)]

	def generate_edges(self, min_e=0, max_e=5, min_w=1, max_w=20):
		for v1 in self.vertices:
			n = random.randint(min_e, max_e)
			adjacent_list = []
			for i in range(n):
				w = random.randint(min_w, max_w)
				v2 = self.vertices[random.randint(0, len(self.vertices)-1)]
				if v2 != v1:
					adjacent_list.append((v2, w))
			self.edges[v1] = adjacent_list

	def outfile(self, fn='testcase.txt'):
		with open(fn, 'w') as f:
			for v1 in self.edges:
				f.write('%s : ' % v1)
				f.write(' '.join(['%s-%d' % (v2, w) for v2, w in self.edges[v1]]))
				f.write('\n')

	def run(self):
		os.system('./run.sh')

	def show(self):
		pass

T = Testcase()
T.run()