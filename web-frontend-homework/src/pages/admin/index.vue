<template>
  <div>
    <div>
      <Nav />
      <div class="imgtable">
        <div class="form-container">
          <Edit :table="tableData" ref="editPannel"/>
          <div>
            <el-table :data="tableData" style="width: 100%">
              <el-table-column prop="name" label="作品名" width="120"></el-table-column>
              <el-table-column prop="author" label="作者" width="120"></el-table-column>
              <el-table-column prop="getTime" label="收录时间" width="120"></el-table-column>
              <el-table-column prop="category" label="类别" width="120"></el-table-column>
              <el-table-column align="center" label="操作" width="155">
                <template slot-scope="scope">
                  <el-button size="small" type="success" @click="edit(scope)">编辑</el-button>
                  <el-button size="small" type="danger" @click="deleteData(scope)">删 除</el-button>
                </template>
              </el-table-column>
            </el-table>
            <div class="pagination">
              <el-pagination
                @current-change="handleCurrentChange"
                :current-page="currentPage"
                :page-size="pagesize"
                layout="total,prev, pager, next"
                :total="amount"
                prev-text="上一页"
                next-text="下一页"
              ></el-pagination>
            </div>
          </div>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
import Nav from "../../components/Nav";
import Edit from "../../components/Edit";
import { deleteArtwork } from "@/api/artwork";
import { getArtworksList } from "@/api/artwork";
import { getArtworksInfo } from "@/api/artwork";
export default {
  name: "admin",
  data() {
    return {
      amount: 0,
      currentPage: 1,
      pagesize: 5,
      list: "",
      tableData: []
    };
  },
  components: {
    Nav,
    Edit
  },
  mounted: function() {
    getArtworksList().then(respose => {
      this.list = respose.data.data;
      this.tableData = this.handleTableData(this.currentPage, this.pagesize);
      this.amount = this.list.length;
    });
  },
  methods: {
    handleTableData: function(currentPage, pagesize) {
      var tableData = [];
      this.list.slice((currentPage - 1) * pagesize, currentPage * pagesize)
        .map(function(item) {
          getArtworksInfo(item).then(response => {
            var dic = response.data.data
            dic["id"] = item
            tableData.push(dic);
          });
        });
      return tableData;
    },

    handleCurrentChange: function(currentPage) {
      this.currentPage = currentPage;
      this.tableData = this.handleTableData(this.currentPage, this.pagesize);
    },
    edit: function(scope) { this.$refs.editPannel.edit(scope.$index, scope.row) },
    deleteData: function(scope) {
      let token = localStorage.getItem('token')
      deleteArtwork(scope.row.id,token).then(() => {
        this.tableData.splice(scope.$index, 1)
      }
      ).catch(error => {
        this.$message.error(Object.values(error.response.data.error_msg)[0])
      })
    }
  }
};
</script>

<style scoped>
.imgtable {
  width: 650px;
  margin: 0 auto;
  margin-top: 80px;
}
.el-col-24 {
  padding-bottom: 300px;
}
</style>
    
